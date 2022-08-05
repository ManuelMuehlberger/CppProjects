#include "document.hpp"

Document::Document(unsigned cc, unsigned nop) : characterCount_{cc}, numberOfPages_{nop}
{
    updateSize();
}

void Document::initialize(std::string str, unsigned type_)
{
    this->setName(str);
    this->setType(type_);
}

void Document::setCharacterCount(unsigned charCount)
{
    this->characterCount_ = charCount;
    updateSize();
}

void Document::setNumberOfPages(unsigned numberOfPages)
{
    this->numberOfPages_ = numberOfPages;
    updateSize();
}

void Document::updateSize()
{
    this->size_ = 10;
    this->size_ += this->characterCount_;
    this->size_ += numberOfPages_ * 25;
}

unsigned Document::numberOfPages()
{
    return numberOfPages_;
}

unsigned Document::characterCount()
{
    return characterCount_;
}