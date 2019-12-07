#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include <vector>

#include "Object.h"
#include "../primitive/Point.h"
#include "../primitive/Quad.h"

class Wall : public Object
{
    private:
        std::vector<Vertex3D*> centerVertexList;
        std::vector<BoundingBox*> boundingBoxList;
        Vertex3D last_pup, last_pdown;

        double wallWidth = 0.1;
        double wallHeight = 0.5;

        int vertexId = 0;

        void updateVertexOrientation();
    public:
        void addPoint(Point* point);
        void removeLastPoint();

        double getWallWidth();
        void increaseWallWidth();
        void decreaseWallWidth();

        double getWallHeight();
        void increaseWallHeight();
        void decreaseWallHeight();

        BoundingBox* getBoundingBox();
        std::vector<BoundingBox*>* getBoundingBoxList();
};

#endif // WALL_H_INCLUDED
