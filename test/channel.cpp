#include <gtest/gtest.h>
#include <Channel.h>
#include <algorithm>
#include <sstream>

/**
 * @test Checks if the operator<< writes to stream on the following format:
 * 1 2 3
 * 4 5 6
 *
 */
TEST(Channel, WritesToStreamOnSpecificFormat)
{
    constexpr auto ExpectedOutput = "1 2 3 \n4 5 6 \n7 8 9 \n\n";

    cv::Mat mat(3, 3, CV_64FC1);
    std::generate(mat.begin<double>(), mat.end<double>(), [n = 1]() mutable { return n++; });
    app::Channel channel{std::move(mat)};

    std::stringstream stringStream;
    stringStream << channel;
    EXPECT_EQ(stringStream.str(), ExpectedOutput);
}

/**
 * @test Checks result of conversion to integral
 */
TEST(Channel, ConvertToIntegral)
{
    std::array<double, 6> expectedNumbers{0, 1, 2, 6, 6, 15};
    const cv::Mat expectedMatrix(3, 2, CV_64FC1, expectedNumbers.data());

    cv::Mat mat(3, 2, CV_64FC1);
    std::generate(mat.begin<double>(), mat.end<double>(), [n = 0]() mutable { return n++; });
    app::Channel channel{std::move(mat)};
    boost::asio::thread_pool threadPool;

    channel.convertToIntegralParallel(threadPool);
    for (auto it = channel.data().begin<double>(), expIt = expectedMatrix.begin<double>();
         expIt != expectedMatrix.end<double>();
        ++it, ++expIt)
    {
        EXPECT_DOUBLE_EQ(*it, *expIt);
    }
}
