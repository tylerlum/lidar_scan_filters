cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread libraries
add_executable(runTests CPP/test_lidar_scan_filters.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
