#include "Quad.h"

using namespace std;

Quad::Quad(Vertex3D* v0, Vertex3D* v1, Vertex3D* v2, Vertex3D* v3)
{
    this->addVertex(v0);
    this->addVertex(v1);
    this->addVertex(v2);
    this->addVertex(v3);
}

Vertex3D* Quad::getV0()
{
    return this->getVertex(0);
}

Vertex3D* Quad::getV1()
{
    return this->getVertex(1);
}

Vertex3D* Quad::getV2()
{
    return this->getVertex(2);
}

Vertex3D* Quad::getV3()
{
    return this->getVertex(3);
}
