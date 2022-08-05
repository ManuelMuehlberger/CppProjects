#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "fileManager.hpp"

#include <iostream>

bool FileManager::addFile(std::string name, unsigned type_)
{
    switch (type_)
    {
    case 1:
    {
        auto p = std::make_shared<Document>();
        p->initialize(name, type_);
        myFiles_.push_back(p);
        if (p->size() <= remainingCapacity())
        {
            usedCapacity_ += p->size();
            return true;
        }
        return false;
    }

    case 2:
    {
        auto p = std::make_shared<Image>();
        p->initialize(name, type_);
        myFiles_.push_back(p);
        if (p->size() <= remainingCapacity())
        {
            usedCapacity_ += p->size();
            return true;
        }
        return false;
    }

    case 3:
    {
        auto p = std::make_shared<Audio>();
        p->initialize(name, type_);
        myFiles_.push_back(p);
        if (p->size() <= remainingCapacity())
        {
            usedCapacity_ += p->size();
            return true;
        }
        return false;
    }

    case 4:
    {
        auto p = std::make_shared<Video>();
        p->initialize(name, type_);
        myFiles_.push_back(p);
        if (p->size() <= remainingCapacity())
        {
            usedCapacity_ += p->size();
            return true;
        }
        return false;
    }
    }

    return false;
}

bool FileManager::addFile(const File &file)
{
    auto added{false};

    auto it = std::find_if(myFiles_.begin(), myFiles_.end(), [&file](auto f)
                           { return f->name() == file.name(); });

    if (it == myFiles_.end() && file.size() <= remainingCapacity())
    {
        myFiles_.push_back(std::make_shared<File>(file));
        usedCapacity_ += file.size();
        added = true;
    }
    return added;
}

bool FileManager::removeFile(std::string str)
{
    for (size_t i = 0; i < myFiles_.size(); i++)
    {
        if (str == myFiles_.at(i)->name())
        {
            usedCapacity_ -= myFiles_.at(i)->size();
            myFiles_.erase(myFiles_.begin() + i);
            return true;
        }
    }
    return false;
}

unsigned FileManager::countFiles()
{
    return myFiles_.size();
}

std::vector<std::shared_ptr<File>> FileManager::findLargerThan(size_t threshold)
{
    std::vector<std::shared_ptr<File>> copy;
    for (auto &&i : myFiles_)
    {
        if (i->size() >= threshold)
        {
            copy.push_back(i);
        }
    }
    return copy;
}

size_t FileManager::remainingCapacity()
{
    return systemCapacity_ - systemLoad();
}

void FileManager::sortByName()
{
    std::sort(myFiles_.begin(), myFiles_.end(), [](std::shared_ptr<File> v1, std::shared_ptr<File> v2)
              { return v1->name() < v2->name(); });
}

void FileManager::sortByType()
{
    std::sort(myFiles_.begin(), myFiles_.end(), sortGroupName);
}

bool FileManager::sortGroupName(const std::shared_ptr<File> v1, const std::shared_ptr<File> v2)
{
    if (v1->type() == v2->type())
    {
        return v1->name() < v2->name();
    }
    else
    {
        return v1->type() < v2->type();
    }
}

void FileManager::sortBySize()
{
    std::sort(myFiles_.begin(), myFiles_.end(), [](std::shared_ptr<File> v1, std::shared_ptr<File> v2)
              { return v1->size() < v2->size(); });
}

size_t FileManager::systemCapacity()
{
    return systemCapacity_;
}

void FileManager::setSystemCapacity(size_t cap)
{
    systemCapacity_ = cap;
}

void FileManager::printFiles()
{
    std::cout << myFiles_.size() << " files are in the system: \n";
    std::cout << "File name:        Type:  File size:\n";
    for (auto entry : myFiles_)
    {
        std::cout << std::setw(16) << entry->name()
                  << std::setw(6) << entry->type()
                  << std::setw(16) << entry->size() << "\n";
    }
    std::cout << std::endl;
}

size_t FileManager::systemLoad()
{
    return usedCapacity_; // TODO
}
