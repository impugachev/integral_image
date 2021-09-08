#include "Channel.h"

#include <boost/thread/latch.hpp> // waiting for c++20...
#include <boost/asio/post.hpp>

namespace app {

Channel::Channel(const cv::Mat& mat)
{
    mat.convertTo(m_mat, CV_64F);
}

void Channel::convertToIntegralParallel(boost::asio::thread_pool& threadPool)
{
    // iterate through diagonals (bottom left - top right)
    for (int line = 1; line < m_mat.rows + m_mat.cols; ++line)
    {
        const auto startCol = std::max(0, line - m_mat.rows);
        const auto count = std::min(line, std::min((m_mat.cols - startCol), m_mat.rows));
        boost::latch latch(count);
        for (int j = 0; j < count; ++j)
        {
            // compute each element asynchronously
            boost::asio::post(threadPool, [j, line, startCol, this, &latch]()
            {
                const auto x = std::min(m_mat.rows, line) - j - 1;
                const auto y = startCol + j;
                auto& elem = m_mat.at<double>(x, y);
                // check boundaries
                if (x != 0)
                    elem += m_mat.at<double>(x - 1, y);
                if (y != 0)
                    elem += m_mat.at<double>(x, y - 1);
                if (x != 0 && y != 0)
                    elem -= m_mat.at<double>(x - 1, y - 1);

                latch.count_down();
            });
        }
        latch.wait(); // wait for whole diagonal
    }
}

const cv::Mat& Channel::data()
{
    return m_mat;
}

std::ostream& operator<<(std::ostream& out, const Channel& channel)
{
    for (int i = 0; i < channel.m_mat.rows; ++i)
    {
        auto row = channel.m_mat.row(i);
        for (auto it = row.begin<double>(); it != row.end<double>(); ++it)
        {
            out << *it << ' ';
        }
        out << '\n';
    }
    out << '\n';
    return out;
}

} // namespace app
