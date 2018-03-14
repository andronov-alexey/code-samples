#pragma once

#include "StrategyBase.h"

class DeleteOldFilesThenCopyNew : public StrategyBase {
private:
	virtual void _reorderTasks(const TaskQueue & _initialTasks) override;
};
