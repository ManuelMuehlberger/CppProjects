#include "video.hpp"

Video::Video(std::array<int, 2> res, unsigned dur) : resolution_{res}, duration_{dur}
{
    updateSize();
}

void Video::initialize(std::string name, unsigned type)
{
    setName(name);
    setType(type);
}

void Video::updateSize()
{
    this->size_ = 10;
    this->size_ += (resolution_.at(0) * resolution_.at(1) * 3 * duration_);
}

std::array<int, 2> Video::resolution()
{
    return resolution_;
}

unsigned Video::duration()
{
    return duration_;
}

void Video::setResolution(std::array<int, 2> res)
{
    resolution_ = res;
    updateSize();
}

void Video::setDuration(unsigned dur)
{
    duration_ = dur;
    updateSize();
}