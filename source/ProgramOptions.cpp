#include "ProgramOptions.h"
#include <iostream>
#include <sstream>

namespace po = boost::program_options;

namespace app {

ProgramOptionsParser::ProgramOptionsParser()
    : m_description{"Allowed options"}
{
    auto threadsChecker =
            [](const size_t& numThreads)
            {
                if (numThreads > 0x7FFFFFFF)
                    throw po::validation_error{
                            po::validation_error::invalid_option_value, "threads", std::to_string(numThreads)};
            };
    m_description.add_options()
            ("help,h", "produce help message")
            ("image,i", po::value<std::vector<std::string>>()->required(),"path to image (required)")
            ("threads,t",
                    po::value<size_t>()->default_value(0)->notifier(threadsChecker),
                    "number of threads, 0 - detect automatically");
}

std::optional<ProgramOptions> ProgramOptionsParser::parse(int argc, const char* const* argv) const
{
    po::variables_map varMap;
    po::store(po::parse_command_line(argc, argv, m_description), varMap);
    if (varMap.count("help"))
        return std::nullopt;
    po::notify(varMap);

    const auto& paths = varMap["image"].as<std::vector<std::string>>();
    return ProgramOptions{{paths.begin(), paths.end()}, varMap["threads"].as<size_t>()};
}

const ProgramOptionsParser::OptionsDescription& ProgramOptionsParser::getDescription() const
{
    return m_description;
}

} // namespace app
