#include "file.hpp"
#pragma once

/** Derived class for audios.
 *  Additionally has a duration and a compressionFactor
 */
class Audio final : public File
{
public:
    Audio(unsigned du = 0, float cf = 1.);

    virtual void initialize(std::string, unsigned) override; // prompts user input to obtain values to set
    unsigned duration();
    float compressionFactor();
    void setDuration(unsigned);
    void setCompressionFactor(float);

protected:
    virtual void updateSize() override; // Updates size according to rules

private:
    unsigned duration_;
    float compressionFactor_;
};