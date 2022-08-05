#include <iostream>
#include <iomanip>
#include "file.hpp"
#include "fileManager.hpp"

enum options
{
    display = 1,
    addFile,
    removeFile,
    countFiles,
    remainingSpace,
    findLarge,
    sortFiles,
    exitProgram = 0
};

int main()
{
    FileManager system;

    auto finished = false;
    int option;

    do
    {
        std::cout << "------ Menu ------\n"
                     "[1] display current files \n"
                     "[2] new file \n"
                     "[3] delete file \n"
                     "[4] countFiles \n"
                     "[5] remaining space \n"
                     "[6] find large files \n"
                     "[7] sort... \n"
                     "[0] exit \n\n";

        std::cout << "Input: ";
        std::cin >> option;
        std::cout << std::endl;

        switch (option)
        {
        case display:
        {
            system.printFiles();
            break;
        }
        case addFile:
        {
            std::cout << "Input new file name: ";
            std::string name;
            std::cin >> name;
            std::cout << "Input file type:\n"
                         "[1] document \n"
                         "[2] image \n"
                         "[3] audio \n"
                         "[4] video \n";
            unsigned type;
            std::cin >> type;
            if (system.addFile(name, type))
                std::cout << "\tFile " << name << " has been added to the system\n\n";
            else
                std::cout << "\tUnable to add file " << name << " \n\n";
            break;
        }
        case removeFile:
        {
            std::cout << "File to delete (name): ";
            std::string name;
            std::cin >> name;
            if (system.removeFile(name))
                std::cout << "\tFile " << name << " has been removed from the system\n\n";
            else
                std::cout << "\tFile " << name << " could not be removed or inexistent\n\n";
            break;
        }
        case countFiles:
        {
            std::cout << "System currently has " << system.countFiles()
                      << " files (occupying " << system.systemLoad()
                      << " of " << system.systemCapacity() << " capacity)\n\n";
            break;
        }
        case remainingSpace:
        {
            std::cout << "System has " << system.remainingCapacity()
                      << " capacity left (out of " << system.systemCapacity() << " max)\n\n";
            break;
        }
        case findLarge:
        {
            std::cout << "Indicate target filesize: ";
            unsigned minSize;
            std::cin >> minSize;
            auto result = system.findLargerThan(minSize);
            std::cout << result.size() << " files were found: \n";
            std::cout << "File name:        Type:  File size:\n";
            for (const auto entry : result)
            {
                std::cout << std::setw(16) << entry->name()
                          << std::setw(6) << entry->type()
                          << std::setw(16) << entry->size() << "\n";
            }
            std::cout << std::endl;
            break;
        }
        case sortFiles:
        {
            std::cout << "sort by... \n"
                         "[1] name \n"
                         "[2] name (grouping by type) \n"
                         "[3] size \n";
            int type;
            std::cin >> type;
            switch (type)
            {
            case 1:
            {
                system.sortByName();
                std::cout << "\tFiles have been sorted by name\n\n";
                break;
            }
            case 2:
            {
                system.sortByType();
                std::cout << "\tFiles have been sorted by name and grouped by type\n\n";
                break;
            }
            case 3:
            {
                system.sortBySize();
                std::cout << "\tFiles have been sorted by size\n\n";
                break;
            }
            default:
            {
                std::cout << "Unknown option, sorting cancelled\n\n";
            }
            }
            break;
        }
        case exitProgram:
        {
            finished = true;
            break;
        }
        default:
        {
            std::cout << "Please enter a valid option!\n\n";
        }
        }
    } while (!finished);

    return 0;
}