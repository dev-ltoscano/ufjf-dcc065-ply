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

        // Obtém a bounding box definida pela classe mãe
        BoundingBox* getBoundingBox(Vertex3D center, double width, double length, double height);

        // Obtém a bounding box definida pela classe filha
        virtual BoundingBox* getCollider() = 0;
};

#endif // COLLIDER_H_INCLUDED
