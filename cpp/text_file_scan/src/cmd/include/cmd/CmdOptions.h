#pragma once

#include <string>
#include <map>

class CmdOptions {
private:
	static const char KEY_PREFIX = '-';

	static bool _isKeyParameter(const std::string & _param);

public:
	CmdOptions(char * _arguments[], int _count);

	bool hasKey(const std::string & _key) const;

	std::string getValue(const std::string & _key) const;

private:
	std::map<std::string, std::string> m_options;
};
