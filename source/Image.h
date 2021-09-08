#ifndef INTEGRAL_IMAGE_IMAGE_H
#define INTEGRAL_IMAGE_IMAGE_H

#include <opencv2/core/mat.hpp>
#include <filesystem>

namespace app {

/**
 * Image on disk
 */
struct Image
{
    std::filesystem::path path; ///< path to image file on disk
    cv::Mat data;               ///< image data
};

/**
 * @brief Read images from disk.
 * Print a error message with image path if reading is failed
 * @param paths paths to images on disk
 * @return successfully read images
 */
std::vector<app::Image> readImages(std::vector<std::filesystem::path> paths);

} // namespace app

#endif //INTEGRAL_IMAGE_IMAGE_H
