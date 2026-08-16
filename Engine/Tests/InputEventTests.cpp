#include "Event/InputEvent.h"

#include <gtest/gtest.h>

using namespace LifeExe;

TEST(InputEventTest, ShouldHoldExpectedAlternativeWhenAssigned)
{
    const EventData data = WindowResizeEventData{1920, 1080};

    EXPECT_TRUE(std::holds_alternative<WindowResizeEventData>(data));
    EXPECT_FALSE(std::holds_alternative<MouseMoveEventData>(data));
    EXPECT_EQ(std::get<WindowResizeEventData>(data).width, 1920);
}

TEST(InputEventTest, ShouldDefaultToMonostateWhenConstructedEmpty)
{
    const EventData data;

    EXPECT_TRUE(std::holds_alternative<std::monostate>(data));
}

TEST(InputEventTest, ShouldReturnNullWhenAccessingWrongAlternative)
{
    const EventData data = WindowResizeEventData{1920, 1080};

    EXPECT_EQ(std::get_if<MouseScrollEventData>(&data), nullptr);
}
