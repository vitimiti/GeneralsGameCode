cmake_minimum_required(VERSION 3.30)
project(GENERALS_AND_ZERO_HOUR LANGUAGES C CXX)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${PROJECT_SOURCE_DIR}/CMakeCache.txt")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/)

include(FeatureSummary)

option(${PROJECT_NAME}_BUILD_GENERALS "Configure C&C Generals for building" ON)

add_feature_info(Build.Generals ${${PROJECT_NAME}_BUILD_GENERALS} "Build Generals project")

if (${PROJECT_NAME}_BUILD_GENERALS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/generals)
endif()

feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "Enabled Features:")
feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "Disabled Features:")
