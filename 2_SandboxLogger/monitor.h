#pragma once
#include "logger.h"
#include <unordered_map>
#include <algorithm>

#include <thread>

/**
 * The File Monitor class keeps a record of files in the targetPath and their last modification time
 * Once the monitor has been started, it will continue checking every interval for new, modified and deleted files
 * until it is stopped
 */
class FileMonitor
{
public:
    // Constructor
    FileMonitor(std::string targetPath,
                std::chrono::milliseconds interval = std::chrono::milliseconds(1'000),
                std::string logFile = "log.txt");

    // run the monitor
    void start(std::chrono::seconds timeout = std::chrono::minutes{1});

private:
    std::unordered_map<std::string, fs::file_time_type> paths_;
    Logger logger_;

    std::string targetPath_;
    std::chrono::duration<int, std::milli> interval_;
    bool running_ = true;

    // Internal method to check if a path is registered
    bool exists(const std::string &path);
};
