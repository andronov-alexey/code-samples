#pragma once

#include "creators/TaskCreator.h"
#include "InputFilenameTaskCreator.h"
#include "WordTaskCreator.h"
#include "tasks/OperationTask.h"

#include <string>

class OperationTaskCreator : public TaskCreator {
public:
	OperationTaskCreator(const Application & _app)
		: TaskCreator(_app, AppOption("-m", "Operation to perform: \"checksum\" or \"count\""))
	{}

private:
	virtual void _createExecutableTasks() override {
		const OperationTask::OPERATION operation = _parseOperation(_getOptionValue());
		const std::string filename = m_app.getCreator<InputFilenameTaskCreator>().getFilename();
		const std::string word = m_app.getCreator<WordTaskCreator>().getWord();
		m_tasks.push_back(std::make_shared<OperationTask>(operation, filename, word));
	}

	OperationTask::OPERATION _parseOperation(const std::string & _operation) const {
		OperationTask::OPERATION operation = OperationTask::OPERATION::UNKNOWN;
		if (_operation == "checksum") {
			operation = OperationTask::OPERATION::CHECKSUM;
		} else if (_operation == "count") {
			operation = OperationTask::OPERATION::COUNT;
		}
		return operation;
	}
};
