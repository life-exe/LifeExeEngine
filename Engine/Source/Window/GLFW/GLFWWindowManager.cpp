#include "GLFWWindowManager.h"
#include "Log/Log.h"
#include <GLFW/glfw3.h>

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogGLFWWindowManager);

GLFWWindowManager::GLFWWindowManager()
{
    glfwSetErrorCallback([](int errorCode, const char* description)  //
        { LE_LOG(LogGLFWWindowManager, Error, "GLFW error, code: {}, description: {}", errorCode, description); });

    if (!glfwInit())
    {
        LE_LOG(LogGLFWWindowManager, Error, "Failed to initialize GLFW!");
        return;
    }

    m_initialized = true;
    LE_LOG(LogGLFWWindowManager, Display, "GLFW initialized successfully!");
}

GLFWWindowManager::~GLFWWindowManager()
{
    m_windows.clear();
    if (m_initialized)
    {
        glfwSetErrorCallback(nullptr);
        glfwTerminate();
    }

    m_initialized = false;
    LE_LOG(LogGLFWWindowManager, Display, "GLFW shutdown complete!");
}

void GLFWWindowManager::update()
{
    if (!m_initialized) return;

    glfwPollEvents();
    cleanupClosedWindows();
}

void GLFWWindowManager::cleanupClosedWindows()
{
    auto it = m_windows.begin();
    while (it != m_windows.end())
    {
        if (it->second->shouldClose())
        {
            LE_LOG(LogGLFWWindowManager, Display, "Remove closed window with id: {}", it->first.value);
            it = m_windows.erase(it);
            continue;
        }
        ++it;
    }
}

bool GLFWWindowManager::areAllWindowsClosed() const
{
    return m_windows.empty();
}

std::expected<WindowId, WindowCreationError> GLFWWindowManager::createWindow(const WindowSettings& settings)
{
    if (!m_initialized)
    {
        LE_LOG(LogGLFWWindowManager, Error, "Cannot create window. GLFW is not initialized.");
        return std::unexpected(WindowCreationError::ManagerIsNotInitialized);
    }

    auto window = std::make_shared<GLFWWindow>(settings);
    if (!window->isValid())
    {
        LE_LOG(LogGLFWWindowManager, Error, "Failed to create GLFW window.");
        return std::unexpected(WindowCreationError::CreationFailed);
    }

    const WindowId id = m_windowIdCounter++;
    m_windows[id] = window;

    LE_LOG(LogGLFWWindowManager, Display, "Added window with id: {}", id.value);

    return id;
}

std::shared_ptr<GLFWWindow> GLFWWindowManager::getWindowById(WindowId id) const
{
    const auto it = m_windows.find(id);
    return it != m_windows.end() ? it->second : nullptr;
}
