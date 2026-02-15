#include "Engine.h"
#include <format>
#include "Log/Log.h"
#include "Window/GLFW/GLFWWindowManager.h"

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine()
{
    LE_LOG(LogEngine, Display, "Initializing Life Exe Engine, version: {}", version());

    m_windowManager = std::make_unique<GLFWWindowManager>();

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
