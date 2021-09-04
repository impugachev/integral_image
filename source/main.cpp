#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

po::variables_map parseOptions(int argc, char* argv[])
{
    po::options_description optDescription{"Allowed options"};
    optDescription.add_options()
            ("help,h", "produce help message")
            ("image,i", po::value<std::vector<std::string>>()->required(),"path to image")
            ("threads,t", po::value<int>()->default_value(0), "number of threads")
            ;
    po::variables_map varMap;
    po::store(po::parse_command_line(argc, argv, optDescription), varMap);
    if (varMap.count("help"))
    {
        std::cout << optDescription << std::endl;
        return varMap;
    }
    po::notify(varMap);
    return varMap;
}


int main(int argc, char* argv[])
{
    try
    {
        auto varMap = parseOptions(argc, argv);
        if (varMap.count("help"))
            return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << std::endl;
        return -1;
    }

    return 0;
}