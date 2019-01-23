project(FileApp)
cmake_minimum_required(VERSION 3.10)

add_subdirectory(src)

FILE(GLOB DOC_FILES "README.md" "docs/*")
add_custom_target(docs SOURCES ${DOC_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT test_app)
