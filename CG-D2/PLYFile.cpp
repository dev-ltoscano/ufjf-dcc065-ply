#include "PLYFile.h"

using namespace std;

PLYFileVersion PLYFile::getFileFormat()
{
    return this->fileFormat;
}

void PLYFile::setFileFormat(PLYFileVersion fileFormat)
{
    this->fileFormat = fileFormat;
}

void PLYFile::addComment(std::string comment)
{
    this->commentList.push_back(comment);
}

std::list<std::string> PLYFile::getCommentList()
{
    return this->commentList;
}

void PLYFile::addElement(PLYFileElement element)
{
    this->elementList.push_back(element);
}

std::list<PLYFileElement> PLYFile::getElementList()
{
    return this->elementList;
}

void PLYFile::addVertex3D(Vertex3D* vertex)
{
    vertexCount++;
    this->vertexList.push_back(vertex);
}

std::vector<Vertex3D*>* PLYFile::getVertexList()
{
    return &this->vertexList;
}

int PLYFile::getVertexCount()
{
    return this->vertexCount;
}

void PLYFile::addFace(Primitive* face)
{
    // Verifica se a face é um triângulo
    if(face->getVertexCount() == 3)
    {
        // Caso seja, incrementa a quantidade de faces em 1
        faceCount++;
    }
    else
    {
        // Caso contrário, incrementa a quantidade de faces em 2, pois é um quadrado
        faceCount += 2;
    }

    this->faceList.push_back(face);
}

std::vector<Primitive*>* PLYFile::getFaceList()
{
    return &this->faceList;
}

int PLYFile::getFaceCount()
{
    return this->faceCount;
}

void PLYFile::addNormal(Vertex3D* normal)
{
    this->normalList.push_back(normal);
}

std::vector<Vertex3D*>* PLYFile::getNormalList()
{
    return &this->normalList;
}
