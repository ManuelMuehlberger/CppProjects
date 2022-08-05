#include "file.hpp"
#include <array>
#pragma once

/** Derived class for images.
 *  Additionally has a resolution (two integers) and a boolean colored
 */
class Image final : public File
{
public:
    Image(std::array<int, 2> res = {0, 0}, bool col = false);

    virtual void initialize(std::string, unsigned) override; // prompts user input to obtain values to set
    std::array<int, 2> resolution();
    bool colored();
    void setResolution(std::array<int, 2>);
    void setColored(bool);

protected:
    virtual void updateSize() override; // Updates size according to rules

private:
    std::array<int, 2> resolution_;
    bool colored_;
};