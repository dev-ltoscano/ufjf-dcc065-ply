#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "../primitive/Vertex3D.h"
#include "../collision/BoundingBox.h"

class Collider
{
    private:
        BoundingBox *boundingBox;
    public:
        Collider();

        // Obt�m a bounding box definida pela classe m�e
        BoundingBox* getBoundingBox(Vertex3D center, double width, double length, double height);

        // Obt�m a bounding box definida pela classe filha
        virtual BoundingBox* getCollider() = 0;
};

#endif // COLLIDER_H_INCLUDED
