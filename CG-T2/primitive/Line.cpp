#include "Line.h"

using namespace std;

Line::Line(Vertex3D* v0, Vertex3D* v1)
{
    this->addVertex(v0);
    this->addVertex(v1);
}

Vertex3D* Line::getV0()
{
    return this->getVertex(0);
}

Vertex3D* Line::getV1()
{
    return this->getVertex(1);
}
