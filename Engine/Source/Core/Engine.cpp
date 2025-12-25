#include "Engine.h"
#include "Log/Log.h"

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine()
{
    LE_LOG(LogEngine, Display, "Initializing Life Exe Engine, version: {}", version());

    LE_LOG_DEBUG(LogEngine, Error, "Error example");
    LE_LOG_DEBUG(LogEngine, Warning, "Warning example");
    LE_LOG(LogEngine, NoLogging, "NoLogging example");
    LE_LOG(LogEngine, Log, "Log file example");
    // LE_LOG(LogEngine, Fatal, "Fatal example");
}
