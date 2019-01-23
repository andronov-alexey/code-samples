#pragma once

#include "creators/TaskCreator.h"
#include "tasks/ProgramUsageTask.h"

#include <memory>

class ProgramUsageTaskCreator : public TaskCreator {
public:
	ProgramUsageTaskCreator(const Application & _app)
		: TaskCreator(_app, AppOption("-h", "Show help"))
	{}

private:
	virtual void _createExecutableTasks() override {
		std::vector<AppOption> availableOptions;

		for (std::shared_ptr<TaskCreator> ptrCreator : m_app.getTaskCreators()) {
			availableOptions.push_back(ptrCreator->getOption());
		}

		m_tasks.push_back(std::make_shared<ProgramUsageTask>(availableOptions));
	}
};
