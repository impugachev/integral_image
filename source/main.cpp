#include "ProgramOptions.h"
#include <iostream>

int main(int argc, char* argv[])
{
    integral_image::ProgramOptionsParser parser;
    try
    {
        auto options = parser.parse(argc, argv);
        if (!options)
        {
            std::cout << parser.getDescription() << std::endl;
        }
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