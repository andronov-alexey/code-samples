#include "DeleteOldFilesThenCopyNew.h"

void DeleteOldFilesThenCopyNew::_reorderTasks(const TaskQueue & /*_initialTasks*/) {
	for (const TaskSPtr & ptrTask : m_downloadGroup) {
		if (ptrTask->getType() == ITask::Type::Download) {
			const QString strStorageRoot = Core::Utils::NavitelDeviceFileSystem::getRoot(ptrTask->getTargetDir().path());
			m_llRequiredLocalSpace[strStorageRoot] += ptrTask->getSpaceCost();
		}
	}

	for (const TaskSPtr & ptrTask : m_removalGroup) {
		if (ptrTask->getType() == ITask::Type::Remove) {
			const QString strStorageRoot = Core::Utils::NavitelDeviceFileSystem::getRoot(ptrTask->getTargetDir().path());
			m_llRequiredDeviceSpace[strStorageRoot] -= ptrTask->getSpaceCost();
		}
	}

	for (const TaskSPtr & ptrTask : m_copyGroup) {
		if (ptrTask->getType() == ITask::Type::Copy) {
			const QString strStorageRoot = Core::Utils::NavitelDeviceFileSystem::getRoot(ptrTask->getTargetDir().path());
			m_llRequiredDeviceSpace[strStorageRoot] += ptrTask->getSpaceCost();
		}
	}

	std::copy(std::cbegin(m_downloadGroup), std::cend(m_downloadGroup), std::back_inserter(m_reorderedTasks));
	std::copy(std::cbegin(m_removalGroup), std::cend(m_removalGroup), std::back_inserter(m_reorderedTasks));
	std::copy(std::cbegin(m_copyGroup), std::cend(m_copyGroup), std::back_inserter(m_reorderedTasks));
	std::copy(std::cbegin(m_cleanupGroup), std::cend(m_cleanupGroup), std::back_inserter(m_reorderedTasks));
}
