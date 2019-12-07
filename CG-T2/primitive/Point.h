#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "Primitive.h"

class Point : public Primitive
{
    public:
        Point(Vertex3D* v0);
        Vertex3D* getV0();
};

#endif // POINT_H_INCLUDED
