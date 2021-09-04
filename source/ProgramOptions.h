#ifndef INTEGRAL_IMAGE_PROGRAMOPTIONS_H
#define INTEGRAL_IMAGE_PROGRAMOPTIONS_H

#include <vector>
#include <string>
#include <optional>

#include <boost/program_options.hpp>

namespace integral_image {

/**
 * Struct for storing program command line arguments
 */
struct ProgramOptions
{
    std::vector<std::string> imagePaths; ///< image paths for processing
    int numThreads;                      ///< number of threads that will be used for computing
};

/**
 * Class for parsing program command line arguments
 */
class ProgramOptionsParser
{
    using OptionsDescription = boost::program_options::options_description;
public:
    ProgramOptionsParser();

    /**
     * Parse command line arguments
     * @param argc number of arguments (including program name)
     * @param argv array of arguments
     * @return std::nullopt if argument "help" is present, filled ProgramOptions otherwise
     */
    [[nodiscard]] std::optional<ProgramOptions> parse(int argc, const char* const* argv) const;

    /**
     * Returns option description
     */
    [[nodiscard]] const OptionsDescription& getDescription() const;

private:
    OptionsDescription m_description;
};

} // namespace integral_image

#endif //INTEGRAL_IMAGE_PROGRAMOPTIONS_H
