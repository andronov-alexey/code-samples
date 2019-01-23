#pragma once

#include "creators/TaskCreator.h"

#include <string>

class InputFilenameTaskCreator : public TaskCreator {
public:
	InputFilenameTaskCreator(const Application & _app)
		: TaskCreator(_app, AppOption("-f", "Input filename"))
	{}

	std::string getFilename() const { return _getOptionValue(); }

private:
	virtual void _createExecutableTasks() override {}
};
