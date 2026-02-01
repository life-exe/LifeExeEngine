# general info
cmake_minimum_required(VERSION 3.31.6)

# cpp options
set(CMAKE_CXX_STANDARD 20)

# common options
project(LifeExeEngine VERSION 1.0.0)
add_executable(${PROJECT_NAME} Source/main.cpp)

# version
configure_file(EngineConfig.h.template ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineConfig.h)

set(ENGINE_SOURCES
    Source/Core/Engine.cpp
    Source/Core/Engine.h
    Source/Core/Utility.h
    .clang-format
    Source/pch.h
    Source/pch.cpp
    Source/EngineConfig.h
    Source/Log/Log.cpp
    Source/Log/Log.h
)

add_library(${PROJECT_NAME}Lib ${ENGINE_SOURCES})
target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)

if(MSVC)
    target_compile_options(${PROJECT_NAME}Lib PUBLIC /Zc:preprocessor)
endif()

# tests
add_executable(${PROJECT_NAME}TestRunner Tests/LogConceptsTest.cpp)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE ${PROJECT_NAME}Lib)

# add libs
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PUBLIC spdlog::spdlog)

find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE gtest::gtest)

# folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine)
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER Engine)

include(${CMAKE_SOURCE_DIR}/Automation/CMAKE/CMakeHelpers.cmake)
create_ide_folders(ENGINE_SOURCES)
setup_precompiled_headers(${PROJECT_NAME}Lib Source/pch.cpp Source/pch.h "${ENGINE_SOURCES}")
