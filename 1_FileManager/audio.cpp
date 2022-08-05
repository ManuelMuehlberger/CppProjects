#include "audio.hpp"

Audio::Audio(unsigned du, float cf) : duration_{du}, compressionFactor_{cf}
{
    updateSize();
}

void Audio::initialize(std::string name, unsigned type)
{
    setName(name);
    setType(type);
}

void Audio::updateSize()
{
    size_ = 10;
    size_ += 16 * duration_ * compressionFactor_;
}

unsigned Audio::duration()
{
    return duration_;
}

float Audio::compressionFactor()
{
    return compressionFactor_;
}

void Audio::setDuration(unsigned dur)
{
    duration_ = dur;
}

void Audio::setCompressionFactor(float cP)
{
    compressionFactor_ = cP;
}