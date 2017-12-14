class FileMaskFilter {
public:
	class FileInfoCmp;
	using FileList = std::set<QFileInfo, FileInfoCmp>;

public:
	FileMaskFilter() = default;
	FileMaskFilter(const QString & _strFilePathMask, bool _bRecursiveSearch = false);

	virtual ~FileMaskFilter() = default;

public:
	FileList getFilteredFiles() const;

	void addIncludeMask(const QString & _mask);
	void addExcludeMask(const QString & _mask);

private:
	FileList _getAllFiles(const QVector<QString> & _masks, bool _bIncludeParentFolderNames = false) const;
	FileList _getFilesByMask(const QVector<QString> & _masks, const QDir::Filters & _flags) const;
	FileList _getFolderFiles(const QDir & _folder) const;
	FileList _getParentFolderNames(const QFileInfo & _file) const;

private:
	QVector<QString> m_includeMasks;
	QVector<QString> m_excludeMasks;

	bool m_bRecursiveSearch { false };
	bool m_bIncludeParentFolderNames { false };
	bool m_bExpandFolders { true };

private:
	QDir::Filters const m_folderFlags { QDir::Dirs | QDir::Readable | QDir::CaseSensitive | QDir::NoDotAndDotDot };
	QDir::Filters const m_fileFlags { QDir::Files | QDir::Readable | QDir::CaseSensitive };
};


class FileMaskFilter::FileInfoCmp {
public:
	bool operator() (const QFileInfo & _lhs, const QFileInfo & _rhs) const {
		return _lhs.isExecutable() == _rhs.isExecutable() ? _lhs.absoluteFilePath() < _rhs.absoluteFilePath() : _rhs.isExecutable();
	}
};
