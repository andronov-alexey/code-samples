class UpdateStrategySelector {
public:
	UpdateStrategySelector();

	void setAvailableDeviceSpace(const QMap<QString, qint64> & _availableDeviceSpace);

	TaskQueue reorderTasks(const TaskQueue & _tasks);

	qint64 getRequiredAdditionalLocalSpace() const;
	qint64 getRequiredAdditionalDeviceSpace() const;

private:
	qint64 _getRequiredAdditionalSpace(const QMap<QString, qint64> & _requiredSpace, QMap<QString, qint64> & _availableSpace);

private:
	// strategies in descending order of preferability
	std::vector<std::unique_ptr<StrategyBase>> m_strategies;

	qint64 m_llMinRequiredAdditionalLocalSpace;
	qint64 m_llMinRequiredAdditionalDeviceSpace;

	QMap<QString, qint64> m_availableDeviceSpace;
};
