#include "tasks/ProgramUsageTask.h"

#include <iostream>

ProgramUsageTask::ProgramUsageTask(const std::vector<AppOption> & _options)
	: m_options(_options)
{
}

void ProgramUsageTask::run() {
	std::cout << "Usage: test_app.exe <options>\n" << "Options:" << std::endl;
	for (const AppOption & option : m_options) {
		std::cout << "\t" << option.getKey() << ",\t--" << option.getDescription() << std::endl;
	}
}
