#include "Brick.h"

Brick::Brick()
{
    Vertex3D *v0 = new Vertex3D(0, -1.0, -1.0, -1.0);
    Vertex3D *v1 = new Vertex3D(1, -1.0, -1.0, 1.0);
    Vertex3D *v2 = new Vertex3D(2, 1.0, -1.0, 1.0);
    Vertex3D *v3 = new Vertex3D(3, 1.0, -1.0, -1.0);

    Vertex3D *v4 = new Vertex3D(4, -1.0, 1.0, -1.0);
    Vertex3D *v5 = new Vertex3D(5, -1.0, 1.0, 1.0);
    Vertex3D *v6 = new Vertex3D(6, 1.0, 1.0, 1.0);
    Vertex3D *v7 = new Vertex3D(7, 1.0, 1.0, -1.0);

    this->addVertex(v0);
    this->addVertex(v1);
    this->addVertex(v2);
    this->addVertex(v3);
    this->addVertex(v4);
    this->addVertex(v5);
    this->addVertex(v6);
    this->addVertex(v7);

    this->addFace(new Quad(v4, v5, v6, v7));
    this->addFace(new Quad(v0, v3, v2, v1));
    this->addFace(new Quad(v0, v1, v5, v4));
    this->addFace(new Quad(v2, v3, v7, v6));
    this->addFace(new Quad(v0, v4, v7, v3));
    this->addFace(new Quad(v2, v6, v5, v1));
}

Brick::Brick(Vertex3D *v0, Vertex3D *v1, Vertex3D *v2, Vertex3D *v3, Vertex3D *v4, Vertex3D *v5, Vertex3D *v6 , Vertex3D *v7)
{
    this->addVertex(v0);
    this->addVertex(v1);
    this->addVertex(v2);
    this->addVertex(v3);
    this->addVertex(v4);
    this->addVertex(v5);
    this->addVertex(v6);
    this->addVertex(v7);

    this->addFace(new Quad(v0, v2, v3, v1));
    this->addFace(new Quad(v5, v7, v6, v4));
    this->addFace(new Quad(v0, v4, v6, v2));
    this->addFace(new Quad(v1, v3, v7, v5));
    this->addFace(new Quad(v2, v6, v7, v3));
    this->addFace(new Quad(v0, v1, v5, v4));
}
