project(test_app)
cmake_minimum_required(VERSION 3.10)

# =========================== Tasks ===========================
set(TASKS_DIR
	tasks
)

set(TASKS_INCLUDE_DIR
	${TASKS_DIR}/include
)

set(TASKS_HEADERS
	${TASKS_INCLUDE_DIR}/tasks/IExecutableTask.h
	${TASKS_INCLUDE_DIR}/tasks/OperationTask.h
	${TASKS_INCLUDE_DIR}/tasks/ProgramUsageTask.h
)
source_group("tasks" FILES ${TASKS_HEADERS})

set(TASKS_SOURCES
	${TASKS_DIR}/OperationTask.cpp
	${TASKS_DIR}/ProgramUsageTask.cpp
)
source_group("tasks" FILES ${TASKS_SOURCES})

list(APPEND TASKS_SOURCES ${TASKS_HEADERS})

# =========================== Creators ===========================
set(CREATORS_DIR
	creators
)

set(CREATORS_INCLUDE_DIR
	${CREATORS_DIR}/include
)

set(CREATORS_SOURCES
	${CREATORS_INCLUDE_DIR}/creators/TaskCreator.h
	${CREATORS_INCLUDE_DIR}/creators/TaskCreator.cpp
	${CREATORS_INCLUDE_DIR}/creators/OperationTaskCreator.h
	${CREATORS_INCLUDE_DIR}/creators/InputFilenameTaskCreator.h
	${CREATORS_INCLUDE_DIR}/creators/WordTaskCreator.h
	${CREATORS_INCLUDE_DIR}/creators/ProgramUsageTaskCreator.h
)
source_group("creators" FILES ${CREATORS_SOURCES})

# =========================== App ===========================
set(APP_DIR
	app
)

set(APP_INCLUDE_DIR
	${APP_DIR}/include
)

set(APP_HEADERS
	${APP_INCLUDE_DIR}/app/AppOption.h
	${APP_INCLUDE_DIR}/app/Application.fwd.h
	${APP_INCLUDE_DIR}/app/Application.h
)
source_group("app" FILES ${APP_HEADERS})

set(APP_SOURCES
	${APP_DIR}/Application.cpp
)
source_group("app" FILES ${APP_SOURCES})

list(APPEND APP_SOURCES ${APP_HEADERS})

# =========================== Cmd ===========================
set(CMD_DIR
	cmd
)

set(CMD_INCLUDE_DIR
	${CMD_DIR}/include
)

set(CMD_HEADERS
	${CMD_INCLUDE_DIR}/cmd/CmdOptions.h
)
source_group("cmd" FILES ${CMD_HEADERS})

set(CMD_SOURCES
	${CMD_DIR}/CmdOptions.cpp
)
source_group("cmd" FILES ${CMD_SOURCES})

list(APPEND CMD_SOURCES ${CMD_HEADERS})

# =========================== Main ===========================
set(SOURCES
	main.cpp
)

add_executable(${PROJECT_NAME}
	${TASKS_SOURCES}
	${CREATORS_SOURCES}
	${APP_SOURCES}
	${CMD_SOURCES}
	${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${TASKS_INCLUDE_DIR}
	${CREATORS_INCLUDE_DIR}
	${APP_INCLUDE_DIR}
	${CMD_INCLUDE_DIR}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
