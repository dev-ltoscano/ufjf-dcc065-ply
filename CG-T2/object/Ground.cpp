#include "Ground.h"

Ground::Ground()
{
    Vertex3D *v0 = new Vertex3D(0, -1.0, 0.0, -1.0);
    Vertex3D *v1 = new Vertex3D(1, -1.0, 0.0, 1.0);
    Vertex3D *v2 = new Vertex3D(2, 1.0, 0.0, 1.0);
    Vertex3D *v3 = new Vertex3D(3, 1.0, 0.0, -1.0);

    this->addVertex(v0);
    this->addVertex(v1);
    this->addVertex(v2);
    this->addVertex(v3);

    this->addFace(new Quad(v0, v1, v2, v3));
}
