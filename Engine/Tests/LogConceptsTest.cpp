#include "Log/Log.h"
#include <gtest/gtest.h>

using namespace LifeExe;

TEST(LogConceptsTest, LogCategoryNameShouldBeValid)
{
    LogCategory category1("TestCategory");
    EXPECT_EQ(category1.name(), "TestCategory");

    LogCategory category2("AnotherCategory");
    EXPECT_EQ(category2.name(), "AnotherCategory");

    EXPECT_NE(category1.name(), category2.name());
}

TEST(LogConceptsTest, LogCategoryTypeShouldBeValid)
{
    static_assert(ValidLogCategory<LogCategory>);
    static_assert(ValidLogCategory<const LogCategory&>);
}

TEST(LogConceptsTest, LogMessageTypeShouldBeValid)
{
    static_assert(LoggableMessage<std::string>);
    static_assert(LoggableMessage<const std::string&>);
    static_assert(LoggableMessage<std::string_view>);
    static_assert(LoggableMessage<const char*>);
    static_assert(LoggableMessage<char*>);

    static_assert(!LoggableMessage<int>);
    static_assert(!LoggableMessage<float>);
    static_assert(!LoggableMessage<bool>);
    static_assert(!LoggableMessage<void*>);
}

TEST(LogConceptsTest, LogVerbosityShouldBeValid)
{
    static_assert(ValidVerbosityLevel<LogVerbosity::NoLogging>);
    static_assert(ValidVerbosityLevel<LogVerbosity::Display>);
    static_assert(ValidVerbosityLevel<LogVerbosity::Error>);
    static_assert(ValidVerbosityLevel<LogVerbosity::Warning>);
    static_assert(ValidVerbosityLevel<LogVerbosity::Fatal>);
    static_assert(ValidVerbosityLevel<LogVerbosity::Log>);
}