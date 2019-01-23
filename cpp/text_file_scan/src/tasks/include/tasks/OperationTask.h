#pragma once

#include "IExecutableTask.h"

#include <string>
#include <iostream>

class OperationTask : public IExecutableTask {
private:
	static const size_t CHECKSUM_WORD_LENGTH_BYTES = 4;

public:
	enum class OPERATION {
		CHECKSUM,
		COUNT,
		UNKNOWN,
	};

public:
	OperationTask(const OPERATION _operation, const std::string & _filename, const std::string & _word)
		: m_operation(_operation)
		, m_filename(_filename)
		, m_word(_word)
	{}

	virtual void run() override {
		switch (m_operation) {
			case OperationTask::OPERATION::CHECKSUM: {
				_calcFileChecksum();
				break;
			}
			case OperationTask::OPERATION::COUNT: {
				_countWords();
				break;
			}
			default: {
				std::cerr << "Error: unknown operation id: " << static_cast<int>(m_operation) << std::endl;
				break;
			}
		}
	}

private:
	void _calcFileChecksum() const;
	void _countWords() const;

private:
	const OPERATION m_operation;
	const std::string m_filename;
	const std::string m_word;
};
