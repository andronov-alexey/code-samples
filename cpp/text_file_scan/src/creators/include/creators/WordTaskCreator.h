#pragma once

#include "creators/TaskCreator.h"

#include <string>

class WordTaskCreator : public TaskCreator {
public:
	WordTaskCreator(const Application & _app)
		: TaskCreator(_app, AppOption("-w", "Word for \"count\" operation"))
	{}

	std::string getWord() const { return _getOptionValue(); }

private:
	virtual void _createExecutableTasks() override {}
};
