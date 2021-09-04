#include "ProgramOptions.h"

#include <gtest/gtest.h>
#include <array>
#include <omp.h>

namespace iimg = integral_image;

struct ProgramOptionsParser : testing::Test
{
    template <typename ...Ts>
    auto parse(Ts... args)
    {
        std::array argv{"integral_image", args...};
        return m_parser.parse(argv.size(), argv.data());
    }

    iimg::ProgramOptionsParser m_parser;
};

TEST_F(ProgramOptionsParser, ReturnsNulloptOnHelpArg)
{
    EXPECT_FALSE(parse("-h"));
}

TEST_F(ProgramOptionsParser, ReturnsImagePathsOnImageArgs)
{
    constexpr std::array Images{"img1", "img2"};
    auto options = parse("-i", Images[0], "-i", Images[1]);
    ASSERT_TRUE(options);
    const auto& parsedImgs = options->imagePaths;
    for (auto i = 0; i < Images.size(); ++i)
        EXPECT_EQ(parsedImgs[i], Images[i]);
}

TEST_F(ProgramOptionsParser, ReturnsOmpMaxThreadsIfThreadsArgIsNotPresent)
{
    auto options = parse("-i", "123");
    ASSERT_TRUE(options);
    EXPECT_EQ(options->numThreads, omp_get_max_threads());
}

TEST_F(ProgramOptionsParser, ReturnsSameNumThreadsAsArg)
{
    auto options = parse("-i", "123", "-t", "1");
    ASSERT_TRUE(options);
    EXPECT_EQ(options->numThreads, 1);
}
