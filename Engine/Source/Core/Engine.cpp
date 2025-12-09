#include "Engine.h"
#include "Log/Log.h"

#include <format>

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine()
{
    Log::getInstance().log(LogEngine, LifeExe::LogVerbosity::Display,  //
        std::format("Initializing Life Exe Engine, version: {}", version()));

    Log::getInstance().log(LogEngine, LifeExe::LogVerbosity::Error, "Error example");
    Log::getInstance().log(LogEngine, LifeExe::LogVerbosity::Warning, "Warning example");
    Log::getInstance().log(LogEngine, LifeExe::LogVerbosity::NoLogging, "NoLogging example");
    Log::getInstance().log(LogEngine, LifeExe::LogVerbosity::Log, "Log file example");
    // Log::getInstance().log(LogEngine, LifeExe::LogVerbosity::Fatal, "Fatal example");
}
