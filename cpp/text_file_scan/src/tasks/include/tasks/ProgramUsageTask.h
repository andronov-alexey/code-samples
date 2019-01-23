#pragma once

#include "IExecutableTask.h"

#include "app/AppOption.h"

#include <vector>


class ProgramUsageTask : public IExecutableTask {
public:
	ProgramUsageTask(const std::vector<AppOption> & _options);

	virtual void run() override;

private:
	const std::vector<AppOption> m_options;
};
