#include "tasks/OperationTask.h"

#include <array>
#include <fstream>
#include <string>

void OperationTask::_calcFileChecksum() const {
	const unsigned short endiannessCheckValue = 1;
	const bool isLittleEndianMachine = (*((unsigned char *)&endiannessCheckValue) != 0);

	std::ifstream file;
	file.open(m_filename, std::ios_base::binary | std::ios_base::in);
	if (!file.is_open()) {
		std::cerr << "Error: unable to open input file " << m_filename << std::endl;
		return;
	}

	uint64_t checksum = 0;
	std::array<char, CHECKSUM_WORD_LENGTH_BYTES> buffer = { 0 };
	while (!file.eof()) {
		buffer.assign(0);
		file.read(buffer.data(), buffer.size());
		if (!isLittleEndianMachine) {
			std::reverse(std::begin(buffer), std::end(buffer));
		}
		checksum += reinterpret_cast<uint32_t &>(*buffer.data());
	}
	file.close();

	std::cout << "File checksum: " << std::showbase << std::uppercase << std::hex << checksum << std::endl;
}

void OperationTask::_countWords() const {
	std::ifstream file;
	file.open(m_filename, std::ios_base::in);
	if (!file.is_open()) {
		std::cerr << "Error: unable to open input file " << m_filename << std::endl;
		return;
	}

	size_t wordCount = 0;
	std::string word;
	while (file >> word) {
		wordCount += (m_word == word);
	}
	file.close();

	std::cout << "Word \"" << m_word << "\" appears " << wordCount << " time(s)" << std::endl;
}
