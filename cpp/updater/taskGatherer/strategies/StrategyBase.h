class StrategyBase {
public:
	void setTasks(const TaskQueue & _tasks);

	TaskQueue getReorderedTasks() const;

	QMap<QString, qint64> getRequiredLocalSpace() const;
	QMap<QString, qint64> getRequiredDeviceSpace() const;

	virtual ~StrategyBase() = default;

protected:
	virtual void _reorderTasks(const TaskQueue & _initialTasks) = 0;

protected:
	QMap<QString, qint64> m_llRequiredLocalSpace;
	QMap<QString, qint64> m_llRequiredDeviceSpace;

	TaskQueue m_downloadGroup;
	TaskQueue m_removalGroup;
	TaskQueue m_copyGroup;
	TaskQueue m_cleanupGroup;

	TaskQueue m_reorderedTasks;
};
