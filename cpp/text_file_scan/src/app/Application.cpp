#include "app/Application.h"

#include "creators/OperationTaskCreator.h"
#include "creators/InputFilenameTaskCreator.h"
#include "creators/WordTaskCreator.h"
#include "creators/ProgramUsageTaskCreator.h"

Application::Application(int _argc, char * _argv[])
	: m_cmdOptions(&_argv[1], _argc - 1)
{
	m_creators.push_back(std::make_shared<OperationTaskCreator>(*this));
	m_creators.push_back(std::make_shared<InputFilenameTaskCreator>(*this));
	m_creators.push_back(std::make_shared<WordTaskCreator>(*this));
	m_creators.push_back(std::make_shared<ProgramUsageTaskCreator>(*this));
}

const CmdOptions & Application::getCmdOptions() const {
	return m_cmdOptions;
}

const std::vector<std::shared_ptr<TaskCreator>> & Application::getTaskCreators() const {
	return m_creators;
}

template <class ConcreteTaskCreator>
const ConcreteTaskCreator & Application::getCreator() const {
	const ConcreteTaskCreator * result = nullptr;
	for (const auto & ptrCreator : m_creators) {
		result = dynamic_cast<const ConcreteTaskCreator *>(ptrCreator.get());
		if (result) {
			return *result;
		}
	}
	throw("No such creator exists");
}
