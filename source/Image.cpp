#include "Image.h"

#include <iostream>
#include <opencv2/imgcodecs.hpp>

namespace app {

std::vector<app::Image> readImages(std::vector<std::filesystem::path> paths)
{
    std::vector<app::Image> images;
    for (auto& path : paths)
    {
        auto imageMat = cv::imread(path.string());
        if (imageMat.empty())
        {
            std::cerr << "Image not found: " << path;
            continue;
        }
        images.push_back(Image{std::move(path), std::move(imageMat)});
    }
    return images;
}

} // namespace app
