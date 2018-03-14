#include "DownloadFilesFirst.h"

void DownloadFilesFirst::_reorderTasks(const TaskQueue & _initialTasks) {
	KeepInitialOrdering::_reorderTasks(_initialTasks);

	const auto pred = [] (const TaskSPtr & task) { return task->getType() == ITask::Type::Download; };

	TaskQueue downloadTasks;

	std::copy_if(std::begin(m_reorderedTasks), std::end(m_reorderedTasks), std::back_inserter(downloadTasks), pred);

	m_reorderedTasks.erase(std::remove_if(std::begin(m_reorderedTasks), std::end(m_reorderedTasks), pred), std::end(m_reorderedTasks));

	std::copy(std::begin(downloadTasks), std::end(downloadTasks), std::inserter(m_reorderedTasks, std::begin(m_reorderedTasks)));
}
