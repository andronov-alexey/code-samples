#pragma once

#include <string>

class AppOption {
public:
	AppOption(const std::string & _key, const std::string & _description)
		: m_key(_key)
		, m_description(_description)
	{}

	std::string getKey() const { return m_key; }
	std::string getDescription() const { return m_description; }

private:
	std::string m_key;
	std::string m_description;
};
