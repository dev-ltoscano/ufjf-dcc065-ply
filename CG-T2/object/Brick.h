#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include "../object/Object.h"

#include "../primitive/RGBColor.h"
#include "../primitive/Vertex3D.h"
#include "../primitive/Quad.h"

class Brick : public Object
{
    public:
        Brick();
        Brick(Vertex3D *v0, Vertex3D *v1, Vertex3D *v2, Vertex3D *v3, Vertex3D *v4, Vertex3D *v5, Vertex3D *v6 , Vertex3D *v7);
};

#endif // BRICK_H_INCLUDED
