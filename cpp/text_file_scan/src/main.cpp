#include "app/Application.h"

#include <vector>
#include <memory>
#include <iostream>

int main(int _argc, char * _argv[]) {
	Application app { _argc, _argv };
	std::vector<std::shared_ptr<IExecutableTask>> tasks;

	for (auto & ptrCreator : app.getTaskCreators()) {
		ptrCreator->createExecutableTasks();
		const auto createdTasks = ptrCreator->getTasks();
		tasks.insert(std::end(tasks), std::begin(createdTasks), std::end(createdTasks));
	}

	for (auto & ptrTask : tasks) {
		ptrTask->run();
	}

	std::cout << std::endl << "Press <enter> to exit ..." << std::endl;
	getchar();
}
