#pragma once

#include "Application.fwd.h"

#include "cmd/CmdOptions.h"
#include "creators/TaskCreator.h"

#include <vector>
#include <memory>

class Application {
public:
	Application(int _argc, char * _argv[]);

	const CmdOptions & getCmdOptions() const;
	const std::vector<std::shared_ptr<TaskCreator>> & getTaskCreators() const;

	template <class ConcreteTaskCreator>
	const ConcreteTaskCreator & getCreator() const;

private:
	CmdOptions m_cmdOptions;
	std::vector<std::shared_ptr<TaskCreator>> m_creators;
};
