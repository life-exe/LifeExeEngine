#include "WinAPIWindowManager.h"
#include "Log/Log.h"

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogWinAPIWindowManager);

WinAPIWindowManager::WinAPIWindowManager()
{
    LE_LOG(LogWinAPIWindowManager, Error, "WinAPI window manager is not implemented!");
}

WinAPIWindowManager::~WinAPIWindowManager() {}

void WinAPIWindowManager::update() {}

bool WinAPIWindowManager::areAllWindowsClosed() const
{
    return true;
}

std::expected<WindowId, WindowCreationError> WinAPIWindowManager::createWindow(const WindowSettings& settings)
{
    return std::unexpected(WindowCreationError::ManagerIsNotInitialized);
}

std::shared_ptr<IWindow> LifeExe::WinAPIWindowManager::getWindowById(WindowId id) const
{
    return nullptr;
}
