#include "PLYObject.h"

using namespace std;

PLYFormatVersion PLYObject::getFileFormat()
{
    return this->fileFormat;
}

void PLYObject::setFileFormat(PLYFormatVersion format)
{
    this->fileFormat = format;
}

void PLYObject::addComment(std::string comment)
{
    this->commentList.push_back(comment);
}

std::list<std::string> PLYObject::getCommentList()
{
    return this->commentList;
}

void PLYObject::addElement(PLYElement element)
{
    this->elementList.push_back(element);
}

std::list<PLYElement> PLYObject::getElementList()
{
    return this->elementList;
}
