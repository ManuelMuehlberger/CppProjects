#include "image.hpp"

Image::Image(std::array<int,2> res, bool col) : resolution_{res}, colored_{col}
{  
    updateSize();
}

void Image::initialize( std::string name, unsigned type_)
{
    setName(name);
    setType(type_);
} 

void Image::updateSize()
{
    this->size_ = 10;
    if(colored_)
    {
        this->size_ += (resolution_.at(0) * resolution_.at(1) * 3);
    }
    else
    {
        this->size_ += (resolution_.at(0) * resolution_.at(1) * 1);
    }
}

bool Image::colored()
{
    return colored_;
}

std::array<int,2> Image::resolution()
{
    return resolution_;
}

void Image::setResolution(std::array<int,2> res)
{
    resolution_ = res;
    updateSize();
}

void Image::setColored(bool b)
{
    colored_ = b;
    updateSize();
}


