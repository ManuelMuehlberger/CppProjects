#include "logger.h"
#include <iostream>

Logger::Logger(std::string filename) : file_{}
{
    // TODO: Check if previous log and/or backup exist
    if (fs::exists(filename))
    {
        std::string newName = filename + "_old";
        rename(filename.c_str(), newName.c_str());
    }

    file_.open(filename);
    if (!file_.is_open())
    {
        std::cout << "Could not open" << std::endl;
        throw std::runtime_error("File could not be opened!");
    }

    std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    file_ << "Commencing logging for directory: " << fs::current_path() << std::endl
          << "Current time is: " << std::ctime(&currentTime) << std::endl;
}

void Logger::log(std::string path, Status fileStatus) const
{
    if (!file_.is_open())
    {
        throw std::runtime_error("File could not be opened!");
    }
    switch (fileStatus)
    {
    case Status::added:
        file_ << " + \t File was added:    " << path << std::endl;
        break;
    case Status::changed:
        file_ << " ! \t File was modified: " << path << std::endl;
        break;
    case Status::removed:
        file_ << " ~ \t File was deleted:  " << path << std::endl;
        break;
    default:
        file_ << " ? \t Error! Unknown file status detected for: " << path << std::endl;

        file_.close();

        break;
    }
}
