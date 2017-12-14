FileMaskFilter::FileMaskFilter(const QString & _strFilePathMask, bool _bRecursiveSearch)
	: m_includeMasks{ _strFilePathMask }, m_bRecursiveSearch(_bRecursiveSearch)
{}

FileMaskFilter::FileList FileMaskFilter::getFilteredFiles() const {
	FileList includedFiles = _getAllFiles(m_includeMasks);
	FileList excludedFiles = _getAllFiles(m_excludeMasks, m_bIncludeParentFolderNames);

	FileList filteredFiles;
	std::set_difference(
		std::begin(includedFiles), std::end(includedFiles),
		std::begin(excludedFiles), std::end(excludedFiles),
		std::inserter(filteredFiles, std::end(filteredFiles)),
		FileInfoCmp()
	);

	return filteredFiles;
}

void FileMaskFilter::addIncludeMask(const QString & _mask) {
	m_includeMasks.push_back(_mask);
}

void FileMaskFilter::addExcludeMask(const QString & _mask) {
	m_excludeMasks.push_back(_mask);
}

FileMaskFilter::FileList FileMaskFilter::_getAllFiles(const QVector<QString> & _masks, bool _bIncludeParentFolderNames) const {
	FileList folderFiles = _getFilesByMask(_masks, m_folderFlags);
	FileList files = _getFilesByMask(_masks, m_fileFlags);

	for (const QFileInfo & folderFile : folderFiles) {
		QDir folder(folderFile.absoluteFilePath());
		files.insert(folder.absolutePath());

		if (!m_bExpandFolders)
			continue;

		FileList folderFiles = _getFolderFiles(folder);
		files.insert(std::begin(folderFiles), std::end(folderFiles));
	}

	if (_bIncludeParentFolderNames) {
		for (const QFileInfo & file : files) {
			FileList parentFolders = _getParentFolderNames(file);
			files.insert(std::begin(parentFolders), std::end(parentFolders));
		}
	}

	return files;
}

FileMaskFilter::FileList FileMaskFilter::_getFilesByMask(const QVector<QString> & _masks, const QDir::Filters & _flags) const {
	FileList filteredFiles;

	for (const QString & strMask : _masks) {
		QDir currentFolder = QFileInfo(strMask).absoluteDir();
		QDirIterator::IteratorFlags iterFlags((m_bRecursiveSearch ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags));

		QDirIterator it(currentFolder.absolutePath(), QStringList() << QFileInfo(strMask).fileName(), _flags, iterFlags);
		while (it.hasNext()) {
			it.next();
			filteredFiles.insert(it.fileInfo());
		}
	}

	return filteredFiles;
}

FileMaskFilter::FileList FileMaskFilter::_getFolderFiles(const QDir & _folder) const {
	FileList files;

	QDirIterator it(_folder.absolutePath(), m_fileFlags | m_folderFlags, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		it.next();
		files.insert(it.fileInfo());
	}

	return files;
}

FileMaskFilter::FileList FileMaskFilter::_getParentFolderNames(const QFileInfo & _file) const {
	FileList pathFolders;
	for (QDir folder = _file.absoluteDir(); !folder.isRoot(); folder.cdUp())
		pathFolders.insert(folder.absolutePath());

	return pathFolders;
}
