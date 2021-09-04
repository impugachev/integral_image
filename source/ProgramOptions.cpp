#include "ProgramOptions.h"
#include <omp.h>
#include <iostream>
#include <sstream>

namespace po = boost::program_options;

namespace integral_image {

ProgramOptionsParser::ProgramOptionsParser()
    : m_description{"Allowed options"}
{
    auto threadsChecker =
            [](const int& numThreads)
            {
                if (numThreads < 0 || numThreads > omp_get_max_threads())
                    throw po::validation_error{
                        po::validation_error::invalid_option_value,"threads", std::to_string(numThreads)};
            };
    m_description.add_options()
            ("help,h", "produce help message")
            ("image,i", po::value<std::vector<std::string>>()->required(),"path to image")
            ("threads,t",
                    po::value<int>()->default_value(omp_get_max_threads())->notifier(threadsChecker),
                    "number of threads, requirements: 0 < t < logical_cores");
}

std::optional<ProgramOptions> ProgramOptionsParser::parse(int argc, const char* const* argv) const
{
    po::variables_map varMap;
    po::store(po::parse_command_line(argc, argv, m_description), varMap);
    if (varMap.count("help"))
        return std::nullopt;
    po::notify(varMap);

    return ProgramOptions{
        varMap["image"].as<std::vector<std::string>>(), // copy... can I move it somehow?
        varMap["threads"].as<int>()};
}

const ProgramOptionsParser::OptionsDescription& ProgramOptionsParser::getDescription() const
{
    return m_description;
}

} // namespace integral_image
