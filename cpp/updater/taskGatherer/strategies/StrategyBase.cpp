#include "StrategyBase.h"

void StrategyBase::setTasks(const TaskQueue & _tasks) {
	QMap<ITask::Type, QVector<TaskSPtr>> reorderableTasks;
	QVector<TaskQueue> unreorderableTasksContainer;

	for (size_t i = 0; i < _tasks.size();) {
		if (_tasks[i]->isReordable()) {
			reorderableTasks[_tasks[i]->getType()].push_back(_tasks[i]);
			i++;
		} else {
			TaskQueue unreorderableTasks;
			for (size_t j = i; j < _tasks.size() && !_tasks[j]->isReordable(); j++, i++) {
				unreorderableTasks.push_back(_tasks[j]);
			}
			unreorderableTasksContainer.push_back(unreorderableTasks);
		}
	}

	for (const TaskQueue & unreorderableTasks : unreorderableTasksContainer) {
		ITask::Type prevalentType = ITask::Type::Unspecified;
		for (const TaskSPtr & ptrTask : unreorderableTasks) {
			if (ptrTask->getType() != ITask::Type::Unspecified) {
				prevalentType = ptrTask->getType();
				break;
			}
		}

		switch (prevalentType) {
			case ITask::Type::Download:
				std::copy(std::cbegin(unreorderableTasks), std::cend(unreorderableTasks), std::back_inserter(m_downloadGroup));
				break;
			case ITask::Type::Remove:
				std::copy(std::cbegin(unreorderableTasks), std::cend(unreorderableTasks), std::back_inserter(m_removalGroup));
				break;
			case ITask::Type::Copy:
				std::copy(std::cbegin(unreorderableTasks), std::cend(unreorderableTasks), std::back_inserter(m_copyGroup));
				break;
			case ITask::Type::Cleanup:
				std::copy(std::cbegin(unreorderableTasks), std::cend(unreorderableTasks), std::back_inserter(m_cleanupGroup));
				break;
			case ITask::Type::Unspecified:
				std::copy(std::cbegin(unreorderableTasks), std::cend(unreorderableTasks), std::back_inserter(m_cleanupGroup));
				break;
			default:
				Q_ASSERT(false);
				break;
		}
	}

	if (!reorderableTasks[ITask::Type::Unspecified].empty()) {
		Q_ASSERT(false && "Cannot safely reorder unspecified tasks. You should make those tasks unreorderable");
		return;
	}

	std::copy(std::cbegin(reorderableTasks[ITask::Type::Download]), std::cend(reorderableTasks[ITask::Type::Download]), std::back_inserter(m_downloadGroup));
	std::copy(std::cbegin(reorderableTasks[ITask::Type::Remove]), std::cend(reorderableTasks[ITask::Type::Remove]), std::back_inserter(m_removalGroup));
	std::copy(std::cbegin(reorderableTasks[ITask::Type::Copy]), std::cend(reorderableTasks[ITask::Type::Copy]), std::back_inserter(m_copyGroup));
	std::copy(std::cbegin(reorderableTasks[ITask::Type::Cleanup]), std::cend(reorderableTasks[ITask::Type::Cleanup]), std::back_inserter(m_cleanupGroup));

	_reorderTasks(_tasks);
}

QMap<QString, qint64> StrategyBase::getRequiredLocalSpace() const {
	return m_llRequiredLocalSpace;
}

QMap<QString, qint64> StrategyBase::getRequiredDeviceSpace() const {
	return m_llRequiredDeviceSpace;
}

TaskQueue StrategyBase::getReorderedTasks() const {
	return m_reorderedTasks;
}
