#include "creators/TaskCreator.h"

#include "app/Application.h"

TaskCreator::TaskCreator(const Application & _app, const AppOption & _option)
	: m_app(_app)
	, m_option(_option)
{}

void TaskCreator::createExecutableTasks() {
	if (m_app.getCmdOptions().hasKey(m_option.getKey())) {
		_createExecutableTasks();
	}
}

std::vector<std::shared_ptr<IExecutableTask>> TaskCreator::getTasks() const { return m_tasks; }
AppOption TaskCreator::getOption() const { return m_option; }

std::string TaskCreator::_getOptionValue() const {
	return m_app.getCmdOptions().getValue(m_option.getKey());
}
