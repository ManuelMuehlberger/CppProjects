#include <string>
#pragma once

/** Base class for File objects.
 *  Keeps track of a name, type, and size
 *  Type is returned as the corresponding 3 letter string as indicated here:
 *  The possible types are:
 *   1 (document): DOC,
 *   2 (image):    IMG,
 *   3 (audio):    AUD,
 *   4 (video):    VID,
 *   * (unknown):  UNK (for any other value)
 */
class File
{
public:
    File() : size_(10), name_("unnamed"), type_(0) {} // Default constructor
    // Overridden functions
    virtual void initialize(std::string name_, unsigned type_); // Prompts user input depending on initialized type
    // Accessors
    size_t size() const;
    std::string name() const;
    std::string type() const;
    // Mutators
    void setName(std::string);
    void setType(unsigned);

    virtual ~File() {}

protected:
    virtual void updateSize() {} // Updates size according to rules, does nothing here
    size_t size_;

private:
    std::string name_;
    unsigned type_;
};