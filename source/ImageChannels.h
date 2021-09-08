#ifndef INTEGRAL_IMAGE_IMAGECHANNELS_H
#define INTEGRAL_IMAGE_IMAGECHANNELS_H

#include "Image.h"
#include "Channel.h"
#include <vector>
#include <filesystem>
#include <opencv2/core/mat.hpp>

namespace app {

/**
 * Channels of an image on disk
 */
class ImageChannels
{
    using Channels = std::vector<Channel>;
public:
    explicit ImageChannels(const Image& image);
    /**
     * Returns iterator to the first channel in container
     * @return random access iterator
     */
    Channels::iterator begin();
    Channels::iterator end();
    /**
     * Returns number of channels
     */
    size_t size();
    /**
     * Write channels to a file whose name is `image file + postfix`
     * @param filePostfix output file postfix
     */
    void writeToFile(std::string_view filePostfix);
private:
    std::filesystem::path m_pathToImage;
    Channels m_channels;
};

} // namespace app

#endif //INTEGRAL_IMAGE_IMAGECHANNELS_H
