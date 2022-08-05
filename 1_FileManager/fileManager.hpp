#include <memory>
#include <vector>
#include "file.hpp"
#include "document.hpp"
#include "image.hpp"
#include "audio.hpp"
#include "video.hpp"

/** File manager class.
 *  Has functions to comply with the defined requirement as well as helper functions
 */
class FileManager
{
public:
    FileManager(size_t capacity = 1e9) : systemCapacity_{capacity}, usedCapacity_{0} {}
    // Required functions
    bool addFile(std::string name, unsigned type); // returns whether it succeeds: name, type
    bool addFile(const File &);                    // used for testing
    bool removeFile(std::string);                  // returns whether it succeeds
    unsigned countFiles();
    size_t remainingCapacity();
    std::vector<std::shared_ptr<File>> findLargerThan(size_t);
    void sortByName();
    void sortByType(); // alphabetically, grouped by type

    static bool sortGroupName(const std::shared_ptr<File>, const std::shared_ptr<File>);

    void sortBySize();

    size_t systemCapacity();
    void setSystemCapacity(size_t);

    // Helper functions
    void printFiles();
    size_t systemLoad();

private:
    std::vector<std::shared_ptr<File>> myFiles_;
    size_t systemCapacity_;
    size_t usedCapacity_;
};