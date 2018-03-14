#pragma once

#include "KeepInitialOrdering.h"

class DownloadFilesFirst : public KeepInitialOrdering {
private:
	virtual void _reorderTasks(const TaskQueue & _initialTasks) override;
};
