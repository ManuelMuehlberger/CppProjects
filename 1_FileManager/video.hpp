#include "file.hpp"
#include <array>
#pragma once

/** Derived class for Videos.
 *  Additionally has a resolution (two integers) and a duration
 */
class Video final : public File
{
public:
    Video(std::array<int, 2> res = {0, 0}, unsigned dur = 0);

    virtual void initialize(std::string, unsigned) override; // prompts user input to obtain values to set
    std::array<int, 2> resolution();
    unsigned duration();
    void setResolution(std::array<int, 2>);
    void setDuration(unsigned);

protected:
    virtual void updateSize() override; // Updates size according to rules

private:
    std::array<int, 2> resolution_;
    unsigned duration_;
};