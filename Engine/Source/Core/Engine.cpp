#include "Engine.h"
#include "Log/Log.h"

#include <format>

using namespace LifeExe;

Engine::Engine()
{
    Log::getInstance().log(LifeExe::LogVerbosity::Display,  //
        std::format("Initializing Life Exe Engine, version: {}", version()));

    Log::getInstance().log(LifeExe::LogVerbosity::Error, "Error example");
    Log::getInstance().log(LifeExe::LogVerbosity::Warning, "Warning example");
    Log::getInstance().log(LifeExe::LogVerbosity::NoLogging, "NoLogging example");
    Log::getInstance().log(LifeExe::LogVerbosity::Fatal, "Fatal example");
}
