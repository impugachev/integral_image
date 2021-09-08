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
        boost::asio::post(threadPool, [&image, &threadPool](){
            ImageChannels channels{image};
            for (auto& channel : channels)
            {
                boost::asio::post(threadPool, [&channel, &threadPool](){
                    channel.convertToIntegralParallel(threadPool);
                });
            }
            channels.writeToFile(".integral");
        });
    }
    threadPool.join();
}

} // namespace app
