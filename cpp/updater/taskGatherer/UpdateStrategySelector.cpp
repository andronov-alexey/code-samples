#include "UpdateStrategySelector.h"

UpdateStrategySelector::UpdateStrategySelector() {
	m_strategies.push_back(std::make_unique<CopyNewFilesThenDeleteOld>());
	m_strategies.push_back(std::make_unique<DeleteOldFilesThenCopyNew>());
	m_strategies.push_back(std::make_unique<DownloadFilesFirst>());
	m_strategies.push_back(std::make_unique<KeepInitialOrdering>());
}

qint64 UpdateStrategySelector::getRequiredAdditionalLocalSpace() const {
	return m_llMinRequiredAdditionalLocalSpace;
}

qint64 UpdateStrategySelector::getRequiredAdditionalDeviceSpace() const {
	return m_llMinRequiredAdditionalDeviceSpace;
}

void UpdateStrategySelector::setAvailableDeviceSpace(const QMap<QString, qint64> & _availableDeviceSpace) {
	m_availableDeviceSpace = _availableDeviceSpace;
}

TaskQueue UpdateStrategySelector::reorderTasks(const TaskQueue & _tasks) {
	m_llMinRequiredAdditionalLocalSpace = std::numeric_limits<qint64>::max();
	m_llMinRequiredAdditionalDeviceSpace = std::numeric_limits<qint64>::max();

	int nSelectedStrategyIdx = -1;
	QMap<QString, qint64> availableLocalSpace;

	for (size_t i = 0; i < m_strategies.size(); i++) {
		StrategyBase & strategy = *m_strategies[i];
		strategy.setTasks(_tasks);

		qint64 llRequiredAdditionalLocalSpace = _getRequiredAdditionalSpace(strategy.getRequiredLocalSpace(), availableLocalSpace);

		if (llRequiredAdditionalLocalSpace < m_llMinRequiredAdditionalLocalSpace) {
			m_llMinRequiredAdditionalLocalSpace = llRequiredAdditionalLocalSpace;
		}

		qint64 llRequiredAdditionalDeviceSpace = _getRequiredAdditionalSpace(strategy.getRequiredDeviceSpace(), m_availableDeviceSpace);

		if (llRequiredAdditionalDeviceSpace <= 0) {
			nSelectedStrategyIdx = i;
			m_llMinRequiredAdditionalDeviceSpace = llRequiredAdditionalDeviceSpace;
			break;
		} else if (llRequiredAdditionalDeviceSpace < m_llMinRequiredAdditionalDeviceSpace) {
			// when all strategies need additional device space choose the one which requires the least of it
			m_llMinRequiredAdditionalDeviceSpace = llRequiredAdditionalDeviceSpace;
			nSelectedStrategyIdx = i;
		}
	}

	if (nSelectedStrategyIdx != -1) {
		return m_strategies[nSelectedStrategyIdx]->getReorderedTasks();
	} else {
		Q_ASSERT(false);
		return _tasks;
	}
}
