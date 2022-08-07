#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Option {
    char optChar;
    std::string longOptionName;
    bool hasParameter = false;
};

std::string to_string(Option const& option);

class ParsingResult {
public:
    ParsingResult(int argc, char* argv[], std::vector<Option> const& options);

    bool is_present(Option const& option);

    template <typename T>
    bool try_assign(Option const& option, T& target)
    {
        std::stringstream converter;
        if (parsedOptions.count(option.optChar)) {
            converter << parsedOptions[option.optChar];
            converter >> target;
            return true;
        }
        if (parsedLongOptions.count(option.longOptionName)) {
            converter << parsedLongOptions[option.longOptionName];
            converter >> target;
            return true;
        }
        return false;
    }
    
    template <typename T>
    void assign(Option const& option, T& target)
    {
        if (!try_assign(option, target))
            throw std::runtime_error("Option " + to_string(option) + " is required but was not provided");
    }

private:
    std::unordered_map<char, std::string> parsedOptions;
    std::unordered_map<std::string, std::string> parsedLongOptions;
};