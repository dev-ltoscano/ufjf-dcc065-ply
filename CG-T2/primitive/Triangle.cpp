#include "Triangle.h"

using namespace std;

Triangle::Triangle(Vertex3D* v0, Vertex3D* v1, Vertex3D* v2)
{
    this->addVertex(v0);
    this->addVertex(v1);
    this->addVertex(v2);
}

Vertex3D* Triangle::getV0()
{
    return this->getVertex(0);
}

Vertex3D* Triangle::getV1()
{
    return this->getVertex(1);
}

Vertex3D* Triangle::getV2()
{
    return this->getVertex(2);
}
