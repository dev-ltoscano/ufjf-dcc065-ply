#include "Primitive.h"

using namespace std;

void Primitive::addVertex(Vertex3D* vertex)
{
    this->vertexList.push_back(vertex);
}

Vertex3D* Primitive::getVertex(int idVertex)
{
    return this->vertexList.at(idVertex);
}

vector<Vertex3D*>* Primitive::getVertexList()
{
    return &this->vertexList;
}

int Primitive::getVertexCount()
{
    return this->vertexList.size();
}
