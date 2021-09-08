#ifndef INTEGRAL_IMAGE_CHANNEL_H
#define INTEGRAL_IMAGE_CHANNEL_H

#include <boost/asio/thread_pool.hpp>
#include <opencv2/core/mat.hpp>

namespace app {

/**
 * Matrix channel
 */
class Channel
{
public:
    /**
     * @param mat single channel
     */
    explicit Channel(cv::Mat mat);
    /**
     * Convert the channel to integral using thread pool
     */
    void convertToIntegralParallel(boost::asio::thread_pool& threadPool);
    /**
     * Returns a const reference to the inner matrix
     */
    const cv::Mat& data();

    friend std::ostream& operator<<(std::ostream& out, const Channel& channel);
private:
    cv::Mat m_mat;
};

} // namespace app


#endif //INTEGRAL_IMAGE_CHANNEL_H
