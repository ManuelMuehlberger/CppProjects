#pragma once

#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

// namespace fs = std::experimental::filesystem;

enum class Status
{
    added,
    changed,
    removed
};

class Logger
{
public:
    Logger(std::string filename = "log.txt");

    void log(std::string path, Status fileStatus) const;

private:
    mutable std::ofstream file_;
};
