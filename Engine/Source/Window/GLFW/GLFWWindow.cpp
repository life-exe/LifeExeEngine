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
            LE_LOG(LogGLFWWindow, Display, "Window with id={} closed!", thisWindow->m_id.value);

            InputEvent event;
            event.type = EventType::WindowClose;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetFramebufferSizeCallback(m_window,
        [](GLFWwindow* window, int width, int height)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            LE_LOG(LogGLFWWindow, Display, "Resize: width={}, height={}", width, height);

            InputEvent event;
            event.type = EventType::WindowResize;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetKeyCallback(m_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            LE_LOG(LogGLFWWindow, Display, "Key={}, scancode={}", key, scancode);

            InputEvent event;
            event.type = EventType::KeyPress;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetCursorPosCallback(m_window,
        [](GLFWwindow* window, double xpos, double ypos)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            // LE_LOG(LogGLFWWindow, Display, "Mouse position:  x={}, y={}", xpos, ypos);

            InputEvent event;
            event.type = EventType::MouseMove;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetMouseButtonCallback(m_window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            LE_LOG(LogGLFWWindow, Display, "Mouse button:{}, action:{}", button, action);

            InputEvent event;
            event.type = EventType::MouseButton;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetScrollCallback(m_window,
        [](GLFWwindow* window, double xoffset, double yoffset)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            LE_LOG(LogGLFWWindow, Display, "Mouse scroll: xoffset={},yoffset={}", xoffset, yoffset);

            InputEvent event;
            event.type = EventType::MouseScroll;
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
