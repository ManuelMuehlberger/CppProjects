#include "monitor.h"
//#include <iostream>
#include <vector>

FileMonitor::FileMonitor(std::string targetPath, std::chrono::milliseconds interval, std::string logFile)
    : logger_{logFile}, targetPath_{targetPath}, interval_{interval}
{
    for (auto &file : fs::recursive_directory_iterator(targetPath_))
    {
        paths_.insert(std::pair<std::string, fs::file_time_type>{file.path().string(), file.last_write_time()});
        // paths_.at(file.path().string()) = file.last_write_time();
    }
}

// Monitor the targetPath for changes and pass information to the logger in case of differences until timeout is reached!
void FileMonitor::start(std::chrono::seconds timeout)
{
    std::time_t startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    while (running_)
    {
        std::this_thread::sleep_for(interval_);

        // TODO: check current list for deletions
        auto it = paths_.begin();

        std::vector<std::string> removedNames;

        while (it != paths_.end())
        {
            fs::path p{it->first};
            bool isStillPresent = false;

            for (auto file : fs::recursive_directory_iterator(targetPath_))
            {
                if (p == file.path())
                {
                    isStillPresent = true;
                    break;
                }
            }

            if (isStillPresent == false)
            {
                // std::cout << "    deleted file found: " << p.string() <<std::endl;
                logger_.log(p, Status::removed);
                removedNames.push_back(p.string());
            }
            it++;
        }

        std::for_each(removedNames.begin(), removedNames.end(), [=](std::string &s)
                      { paths_.erase(s); });

        // TODO: Check directory for new or modified entries
        for (auto file : fs::recursive_directory_iterator(targetPath_))
        {
            auto lastChangeToFile = fs::last_write_time(file);
            auto fileName = file.path().string();

            // Case 1: neue Datei -> kein match
            if (paths_.find(fileName) == paths_.end())
            {
                // std::cout << "    new file found: " << fileName << std::endl;
                std::pair<std::string, fs::file_time_type> pair{file.path().string(), lastChangeToFile};
                paths_.insert(pair);
                logger_.log(file.path().string(), Status::added);
            }

            // Case 2: gleicher Name -> veränderte last_write_time
            else if (paths_.find(fileName) != paths_.end() && paths_.at(file.path().string()) < lastChangeToFile)
            {
                // std::cout << "    changed file found" << std::endl;
                paths_.at(file.path().string()) = lastChangeToFile;
                logger_.log(file.path().string(), Status::changed);
            }

            else
            {
                // std::cout << "    no changes found for: " << file.path().string() << std::endl;
            }
        }

        // Check if monitor should stop -> aktuelle Zeit >= startTime + timeout
        if (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) >= startTime + timeout.count())
        {
            running_ = false;
        }
    }
}

bool FileMonitor::exists(const std::string &path)
{
    return paths_.find(path) != paths_.end();
}
