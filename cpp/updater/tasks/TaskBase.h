class TaskBase : public QObject {
	Q_OBJECT

public:
	enum class ErrorType {
		FatalError,
		RenewableError
	};
	Q_ENUM(ErrorType)

	enum class Type {
		Download,
		Copy,
		Remove,
		Cleanup,
		Unspecified,
	};

public:
	TaskBase(quint64 _spaceCostBytes = 0, Type _type = Type::Unspecified);
	virtual ~TaskBase() = default;

public:
	void start();

	void interrupt();
	void revert();

	bool isInterrupted() const;

	QString getDescription() const;
	Type getType() const;

	qint64 getSpaceCost() const;
	QDir getTargetDir() const;

signals:
	void sigTaskStarted(const TaskBase *);
	void sigTaskProgress(const TaskBase *, TaskProgressInfo::DataType , qint64, qint64) const;
	void sigTaskCompleted(const TaskBase *);
	void sigTaskInterrupted(const TaskBase *);
	void sigTaskError(TaskBase *, ErrorType _type, const QString & _strDescription);

protected:
	void _processLoopMessages() const;
	void _reportError(ErrorType _type, const QString & _strDescription);

	bool _removeFile(const QString & _strFilePath) const;
	void _createFolder(const QDir & _path) const;

protected:
	const Type m_type;
	bool m_bInterrupted;
	qint64 m_llSpaceCostBytes;
	QDir m_targetDir;

private:
	virtual void _start();
	virtual void _revert();
	virtual void _init();

	virtual QString _getDescription() const;
};
