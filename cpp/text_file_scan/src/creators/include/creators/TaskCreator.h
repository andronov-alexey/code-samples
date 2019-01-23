#pragma once

#include "app/AppOption.h"
#include "app/Application.fwd.h"
#include "tasks/IExecutableTask.h"

#include <vector>
#include <memory>
#include <string>

class TaskCreator {
public:
	TaskCreator(const Application & _app, const AppOption & _option);

	void createExecutableTasks();

	std::vector<std::shared_ptr<IExecutableTask>> getTasks() const;
	AppOption getOption() const;

protected:
	std::string _getOptionValue() const;

private:
	virtual void _createExecutableTasks() = 0;

protected:
	const Application & m_app;
	const AppOption m_option;
	std::vector<std::shared_ptr<IExecutableTask>> m_tasks;
};
