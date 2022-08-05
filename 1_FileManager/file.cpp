#include "file.hpp"
#include "document.hpp"

void File::initialize(std::string name, unsigned type)
{
    this->name_ = name;
    this->type_ = type;
}

size_t File::size() const
{
    return this->size_;
}

std::string File::name() const
{
    return this->name_;
}

std::string File::type() const
{
    switch (this->type_)
    {
    case 1:
        return "DOC";
    case 2:
        return "IMG";
    case 3:
        return "AUD";
    case 4:
        return "VID";
    default:
        return "UNK";
    }
}

void File::setName(std::string name)
{
    this->name_ = name;
}

void File::setType(unsigned type)
{
    this->type_ = type;
}
