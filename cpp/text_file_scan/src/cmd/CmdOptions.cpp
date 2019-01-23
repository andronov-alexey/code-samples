#include "cmd/CmdOptions.h"

#include <iostream>

bool CmdOptions::_isKeyParameter(const std::string & _param) {
	return (!_param.empty() && _param[0] == KEY_PREFIX);
}

CmdOptions::CmdOptions(char * _arguments[], int _count) {
	for (int i = 0; i < _count; i++) {
		std::string key = _arguments[i];
		if (_isKeyParameter(key)) {
			std::string value;
			if (i + 1 < _count) {
				if (!_isKeyParameter(_arguments[i + 1])) {
					value = _arguments[i + 1];
					++i;
				}
			}
			m_options[key] = value;
		} else {
			std::cerr << "Parameter '" << key << "' is not a valid option" << std::endl;
		}
	}
}

bool CmdOptions::hasKey(const std::string & _key) const {
	return m_options.count(_key) != 0;
}

std::string CmdOptions::getValue(const std::string & _key) const {
	return hasKey(_key) ? m_options.at(_key) : "";
}
