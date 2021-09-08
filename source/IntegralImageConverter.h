#ifndef INTEGRAL_IMAGE_INTEGRALIMAGECONVERTER_H
#define INTEGRAL_IMAGE_INTEGRALIMAGECONVERTER_H

#include "Image.h"

#include <vector>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <optional>

namespace app {

/**
 * Converts an image to its integral representation
 */
class IntegralImageConverter
{
public:
    /**
     * @param numThreads the number of threads used for conversion
     */
    explicit IntegralImageConverter(size_t numThreads);
    /**
     * Converts an image and writes to a files `image_path.integral`
     * @param images images to be converted
     */
    void toFiles(const std::vector<Image>& images);
private:
    // std::optional for defer construction
    std::optional<boost::asio::thread_pool> m_threadPool;
};

} // namespace app

#endif //INTEGRAL_IMAGE_INTEGRALIMAGECONVERTER_H
