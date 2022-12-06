cmake_minimum_required( VERSION 3.13 )

# Project settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(PROJECT_UNIT_TESTS_NAME ${PROJECT_NAME_STR}_Graph_UnitTest)

# Dependencies
find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

# Assign the include directories
# Include paths: List of directories of common header files (-I).
include_directories(
    mylib/include
    mylib/include/mylib

    /usr/local
    /usr/local/include

    ${Boost_INCLUDE_DIRS}
)

# # Build unit tests
add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(${PROJECT_UNIT_TESTS_NAME} testGraph.cpp)
target_link_libraries(
    ${PROJECT_UNIT_TESTS_NAME}
    ${OUTPUT_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

enable_testing()
add_test(NAME MyGraphTest COMMAND GraphTest)
