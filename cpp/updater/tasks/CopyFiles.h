class CopyFiles : public TaskBase, private FileMaskFilter {
	Q_OBJECT

public:
	CopyFiles(const QString & _strSrcFilePathMask, const QDir & _destFolder, const QString & _strFileDescription, bool _bRecursive = false);

	void setInterruptable(bool _bCanBeInterrupted = true);

private:
	virtual void _start() override;
	virtual void _init() override;

	virtual QString _getDescription() const override;

private:
	bool _copyFile(const QFileInfo & _file, QString & _strErrorStringOutput) const;

	void _reportFileProgress(qint64, qint64) const;
	bool _isCopyInterrupted() const;

private:
	static const uint ms_uCopyBufSize = 2 * 1024 * 1024; // 2 MB
	static const uint ms_uMaxSeqBlockWritingsCount = 10;

private:
	QDir const m_srcFolder;
	QDir const m_destFolder;
	QString const m_strFileDescription;

	FileMaskFilter::FileList m_filesToCopy;

	qint64 mutable m_llProcessedBytesCount;
	uint mutable m_uBlockWritingsCount;

	bool m_bCanBeInterrupted;
};
