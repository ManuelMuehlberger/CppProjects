#include "file.hpp"
#pragma once

/** Derived class for documents.
 *  Additionally has a characterCount and numberOfPages
 */
class Document final : public File
{
public:
    Document(unsigned characterCount = 0, unsigned numberOfPages = 0);

    virtual void initialize(std::string name, unsigned type) override; // prompts user input to obtain values to set ->cC nOP
    unsigned characterCount();
    unsigned numberOfPages();
    void setCharacterCount(unsigned);
    void setNumberOfPages(unsigned);

protected:
    virtual void updateSize() override; // Updates size according to rules

private:
    unsigned characterCount_;
    unsigned numberOfPages_;
};