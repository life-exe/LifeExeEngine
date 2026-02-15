#pragma once
#include <string>
#include <functional>

class GLFWwindow;

namespace LifeExe
{

struct WindowId
{
    unsigned int value{0};
    constexpr explicit WindowId(unsigned int id) : value(id) {}

    constexpr WindowId operator++(int)
    {
        WindowId temp = *this;
        ++value;
        return temp;
    }

    constexpr auto operator<=>(const WindowId&) const = default;
};

struct WindowSettings
{
    std::string title{};
    int width{800};
    int height{600};
    int x{50};
    int y{50};
};

class GLFWWindow final
{
public:
    GLFWWindow(const WindowSettings& settings);
    ~GLFWWindow();

    void setTitle(const std::string& title);
    bool isValid() const;
    bool shouldClose() const;

private:
    GLFWwindow* m_window{nullptr};
};

}  // namespace LifeExe

namespace std
{
template <>
struct hash<LifeExe::WindowId>
{
    size_t operator()(const LifeExe::WindowId& id) const noexcept  //
    {
        return std::hash<unsigned int>{}(id.value);
    }
};
}  // namespace std