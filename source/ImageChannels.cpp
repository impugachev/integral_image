#include "ImageChannels.h"
#include <opencv2/core.hpp>
#include <fstream>

namespace app {

ImageChannels::ImageChannels(const Image& image)
    : m_pathToImage(image.path)
{
    std::vector<cv::Mat> buffer;
    cv::split(image.data, buffer); // does not accept an iterator, so a buffer is needed
    m_channels.insert(m_channels.begin(), buffer.begin(), buffer.end());
}

ImageChannels::Channels::iterator ImageChannels::begin()
{
    return m_channels.begin();
}

ImageChannels::Channels::iterator ImageChannels::end()
{
    return m_channels.end();
}

size_t ImageChannels::size()
{
    return m_channels.size();
}

void ImageChannels::writeToFile(std::string_view filePostfix)
{
    auto newPath = m_pathToImage;
    newPath += filePostfix;
    std::ofstream integralFile{newPath};
    for (const auto& channel : m_channels)
    {
        integralFile << channel;
    }
}

} // namespace app
