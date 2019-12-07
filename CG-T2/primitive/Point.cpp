#include "Point.h"

Point::Point(Vertex3D* v0)
{
    this->addVertex(v0);
    this->setColor(RGBColor(1.0, 0.0, 1.0));
}

Vertex3D* Point::getV0()
{
    return this->getVertex(0);
}
