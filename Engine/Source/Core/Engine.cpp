#include "Engine.h"
#include <format>
#include "Log/Log.h"
#include "Window/IWindowManager.h"

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine(std::unique_ptr<IWindowManager> windowManager)  //
    : m_windowManager(std::move(windowManager))
{
    LE_LOG(LogEngine, Display, "Initializing Life Exe Engine, version: {}", version());

    const auto windowResult = m_windowManager->createWindow(WindowSettings{});
    if (!windowResult)
    {
        LE_LOG(LogEngine, Error, "Failed to create main window");
        return;
    }

    if (auto window = m_windowManager->getWindowById(windowResult.value()))
    {
        window->setTitle(std::format("Life Exe Engine, version: {}", version()));
    }

    m_initialized = true;
}

Engine::~Engine() = default;

void Engine::run()
{
    if (!m_initialized)
    {
        LE_LOG(LogEngine, Error, "Cannot run: LifeExe engine is not initialized...");
        return;
    }

    while (!m_windowManager->areAllWindowsClosed())
    {
        m_windowManager->update();
    }
}
