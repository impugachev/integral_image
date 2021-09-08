#include "ProgramOptions.h"
#include "IntegralImageConverter.h"

#include <iostream>

using namespace app;

int main(int argc, char* argv[])
{
    app::ProgramOptionsParser parser;
    try
    {
        auto options = parser.parse(argc, argv);
        if (!options)
        {
            std::cout << parser.getDescription() << std::endl;
            return 0;
        }
        auto images = readImages(std::move(options->imagePaths));
        IntegralImageConverter converter{options->numThreads};
        converter.toFiles(images);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << std::endl;
        return -2;
    }
    return 0;
}