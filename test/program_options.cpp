#include "ProgramOptions.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>

struct ProgramOptionsParser : testing::Test
{
    template <typename ...Ts>
    auto parse(Ts... args)
    {
        std::array argv{"integral_image", args...};
        return m_parser.parse(argv.size(), argv.data());
    }

    app::ProgramOptionsParser m_parser;
};

/**
 * @test Checks if parse returns std::nullopt if help argument is present
 */
TEST_F(ProgramOptionsParser, ReturnsNulloptOnHelpArg)
{
    EXPECT_FALSE(parse("-h"));
}

/**
 * @test Checks if parse returns the same images paths as in arguments
 */
TEST_F(ProgramOptionsParser, ReturnsImagePathsOnImageArgs)
{
    constexpr std::array Images{"img1", "img2"};
    auto options = parse("-i", Images[0], "-i", Images[1]);
    ASSERT_TRUE(options);
    EXPECT_THAT(options->imagePaths, testing::ElementsAreArray(Images));
}

/**
 * @test Checks if parse returns 0 threads if thread argument is not present
 */
TEST_F(ProgramOptionsParser, ReturnsZeroIfThreadsArgIsNotPresent)
{
    auto options = parse("-i", "123");
    ASSERT_TRUE(options);
    EXPECT_EQ(options->numThreads, 0);
}

/**
 * @test Checks if parse returns same threads number as in arguments
 */
TEST_F(ProgramOptionsParser, ReturnsSameNumThreadsAsArg)
{
    auto options = parse("-i", "123", "-t", "123");
    ASSERT_TRUE(options);
    EXPECT_EQ(options->numThreads, 123);
}
