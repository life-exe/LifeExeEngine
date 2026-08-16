#include "GLFWWindow.h"
#include "Log/Log.h"
#include <GLFW/glfw3.h>

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogGLFWWindow);

GLFWWindow::GLFWWindow(WindowId id, const WindowSettings& settings)  //
    : m_id(id)
{
    // init ->
    m_window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        LE_LOG(LogGLFWWindow, Error, "Failed to create GLFW window!");
        return;
    }
    glfwSetWindowPos(m_window, settings.x, settings.y);

    // user pointer ->
    glfwSetWindowUserPointer(m_window, this);

    // events ->
    glfwSetWindowCloseCallback(m_window,
        [](GLFWwindow* window)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

            InputEvent event;
            event.type = EventType::WindowClose;
            event.data = WindowCloseEventData{thisWindow->m_id.value};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetFramebufferSizeCallback(m_window,
        [](GLFWwindow* window, int width, int height)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

            InputEvent event;
            event.type = EventType::WindowResize;
            event.data = WindowResizeEventData{width, height};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetKeyCallback(m_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

            InputEvent event;
            event.type = EventType::KeyPress;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetCursorPosCallback(m_window,
        [](GLFWwindow* window, double xpos, double ypos)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

            InputEvent event;
            event.type = EventType::MouseMove;
            event.data = MouseMoveEventData{xpos, ypos};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetMouseButtonCallback(m_window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

            InputEvent event;
            event.type = EventType::MouseButton;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetScrollCallback(m_window,
        [](GLFWwindow* window, double xoffset, double yoffset)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));

            InputEvent event;
            event.type = EventType::MouseScroll;
            event.data = MouseScrollEventData{xoffset, yoffset};
            thisWindow->m_windowEvent.invoke(event);
        });
}

GLFWWindow::~GLFWWindow()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void GLFWWindow::setTitle(const std::string& title)
{
    if (!m_window) return;
    glfwSetWindowTitle(m_window, title.c_str());
}

bool GLFWWindow::isValid() const
{
    return m_window != nullptr;
}

bool GLFWWindow::shouldClose() const
{
    if (!m_window) return true;
    return glfwWindowShouldClose(m_window);
}

Event<const InputEvent&>& GLFWWindow::windowEvent()
{
    return m_windowEvent;
}
