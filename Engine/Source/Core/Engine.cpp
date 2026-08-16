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
        window->windowEvent().add(this, &Engine::onWindowEvent);
        // window->windowEvent().add([](const InputEvent& event) {});
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

void Engine::onWindowEvent(const InputEvent& event)
{
    //  LE_LOG(LogGLFWWindow, Display, "Mouse button:{}, action:{}", button, action);
    //  LE_LOG(LogGLFWWindow, Display, "Key={}, scancode={}", key, scancode);

    if (auto* data = std::get_if<MouseScrollEventData>(&event.data))
    {
        LE_LOG(LogEngine, Display, "Mouse scroll: xoffset={},yoffset={}", data->xOffset, data->yOffset);
    }
    else if (auto* data = std::get_if<MouseMoveEventData>(&event.data))
    {
        LE_LOG(LogEngine, Display, "Mouse position:  x={}, y={}", data->x, data->y);
    }
    else if (auto* data = std::get_if<WindowResizeEventData>(&event.data))
    {
        LE_LOG(LogEngine, Display, "Resize: width={}, height={}", data->width, data->height);
    }
    else if (auto* data = std::get_if<WindowCloseEventData>(&event.data))
    {
        LE_LOG(LogEngine, Display, "Window with id={} closed!", data->id);
    }
}
