#include "IntegralImageConverter.h"

#include "ImageChannels.h"

namespace app {

IntegralImageConverter::IntegralImageConverter(size_t numThreads)
{
    if (numThreads == 0)
        m_threadPool.emplace(); // will determine the number of threads itself
    else
        m_threadPool.emplace(numThreads);
}

void IntegralImageConverter::toFiles(const std::vector<Image>& images)
{
    auto& threadPool = *m_threadPool;
    for (const auto& image : images)
    {
        boost::asio::post(threadPool, [im = &image, &threadPool](){
            ImageChannels channels{*im};
            for (auto& channel : channels)
            {
                boost::asio::post(threadPool, [ch = &channel, &threadPool](){
                    ch->convertToIntegralParallel(threadPool);
                });
            }
            channels.writeToFile(".integral");
        });
    }
    threadPool.join();
}

} // namespace app
