#include "Window/IWindow.h"
#include <gtest/gtest.h>

using namespace LifeExe;

TEST(WindowIdTest, WindowIdIncrementShouldWorkCorrectly)
{
    WindowId id{13};
    const WindowId original = id;
    const WindowId after = id++;

    EXPECT_EQ(original.value, 13);
    EXPECT_EQ(after.value, 13);
    EXPECT_EQ(id.value, 14);
}

TEST(WindowIdTest, WindowIdComparisonShouldWorkCorrectly)
{
    const WindowId id1{5};
    const WindowId id2{5};
    const WindowId id3{10};

    EXPECT_EQ(id1, id2);
    EXPECT_NE(id1, id3);
    EXPECT_LT(id1, id3);
}
