#include "command_line_parser.hpp"

std::string to_string(Option const& option)
{
    std::stringstream builder;
    builder << "{ -" << option.optChar << " / --" << option.longOptionName << "}";
    return builder.str();
}

bool ParsingResult::is_present(Option const& option)
{
    return parsedOptions.count(option.optChar) || parsedLongOptions.count(option.longOptionName);
}

ParsingResult::ParsingResult(int argc, char* argv[], std::vector<Option> const& options)
{
    std::stringstream ss;
    for (int i = 1; i < argc; i++) ss << argv[i] << "\n";
    std::string arg;
    while (std::getline(ss, arg)) {
        if (arg[0] != '-') {  // Not an option
            remainingArguments.push_back(arg);
            continue;
        }
        // Go over all chars, so you can chain options. e.g. -a -b -c == -abc
        for (size_t i = 1; i < arg.size(); i++) {
            char optChar = arg[i];
            if (i == 1 && optChar == '-' && arg.size() > 2) {  // Options is a long option
                std::string longOption = arg.substr(2);
                // Find Option if available
                auto option = std::find_if(options.begin(), options.end(),
                                           [&](Option const& o) { return o.longOptionName == longOption; });
                if (option == std::end(options)) {
                    std::cerr << "[CL Parser] Unknown long option: " << longOption << "\n";
                    continue;
                }
                if (option->hasParameter) std::getline(ss, parsedLongOptions[longOption]);
                // Stop processing the rest of the argument string
                break;
            }  
            // Option is a short option
            auto option =
                std::find_if(options.begin(), options.end(), [&](Option const& o) { return o.optChar == optChar; });
            if (option == std::end(options)) {
                std::cerr << "[CL Parser] Unkown option: " << optChar << "\n";
                continue;
            }
            parsedOptions[optChar] = "";
            if (!option->hasParameter) continue;
            if ((i + 1) < arg.size()) {  // Rest of arg-string is the parameter
                parsedOptions[optChar] = arg.substr(i + 1);
                break;
            }
            // The next argument is a parameter
            std::getline(ss, parsedOptions[optChar]);
        }
    }
}