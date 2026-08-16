#include "Event/Event.h"
#include <gtest/gtest.h>

using namespace LifeExe;

TEST(EventTest, ShouldCallSubscriberWhenInvoked)
{
    Event<int> event;
    int recieved{0};
    event.add([&recieved](int value) { recieved = value; });

    EXPECT_EQ(recieved, 0);
    event.invoke(42);
    EXPECT_EQ(recieved, 42);
}

TEST(EventTest, ShouldStopDeliveryWhenSubscriberRemoved)
{
    Event<int> event;
    int callCount{0};
    const auto handle = event.add([&callCount](int) { ++callCount; });

    EXPECT_EQ(callCount, 0);
    event.invoke(15);
    EXPECT_EQ(callCount, 1);
    event.invoke(67);
    EXPECT_EQ(callCount, 2);

    event.remove(handle);
    event.invoke(33);
    EXPECT_EQ(callCount, 2);
}

namespace
{
struct Listener
{
    int value{0};
    void onValue(int val) { value = val; }
};
}  // namespace

TEST(EventTest, ShouldCallMemberFunctionWhenSubscribed)
{
    Event<int> event;
    Listener listener;
    EXPECT_EQ(listener.value, 0);

    event.add(&listener, &Listener::onValue);
    event.invoke(99);

    EXPECT_EQ(listener.value, 99);
}
