#include "Vertex3D.h"

using namespace std;

Vertex3D::Vertex3D()
{
    this->id = -1;
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vertex3D::Vertex3D(int id, double x, double y, double z)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->z = z;
}

int Vertex3D::getId()
{
    return this->id;
}

double Vertex3D::getX()
{
    return this->x;
}

double Vertex3D::getY()
{
    return this->y;
}

double Vertex3D::getZ()
{
    return this->z;
}

void Vertex3D::setX(double x)
{
    this->x = x;
}

void Vertex3D::setY(double y)
{
    this->y = y;
}

void Vertex3D::setZ(double z)
{
    this->z = z;
}
