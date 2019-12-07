#include "Wall.h"
#include <iostream>

using namespace std;

void Wall::updateVertexOrientation()
{
    Vertex3D *c0 = centerVertexList.at(centerVertexList.size() - 2);
    Vertex3D *c1 = centerVertexList.at(centerVertexList.size() - 1);

    int currentIndex = (getVertexCount() - 1);

    Vertex3D *v0 = getVertex(currentIndex - 7);
    Vertex3D *v1 = getVertex(currentIndex - 6);
    Vertex3D *v2 = getVertex(currentIndex - 5);
    Vertex3D *v3 = getVertex(currentIndex - 4);

    Vertex3D *v4 = getVertex(currentIndex - 3);
    Vertex3D *v5 = getVertex(currentIndex - 2);
    Vertex3D *v6 = getVertex(currentIndex - 1);
    Vertex3D *v7 = getVertex(currentIndex);

    /* Encontra vetor ente os pontos centrais */
    Vertex3D u;
    u.setX(c1->getX() - c0->getX());
    u.setZ(c1->getZ() - c0->getZ());

    /* Encontra dois vetores ortogonais a u */
    Vertex3D pup, pdown;
    pup.setX(-u.getZ());
    pup.setZ(u.getX());

    pdown.setX(u.getZ());
    pdown.setZ(-u.getX());

    float val_0 = sqrt(pow(pup.getX(), 2) + pow(pup.getZ(), 2));
    float val_1 = sqrt(pow(pdown.getX(), 2) + pow(pdown.getZ(), 2));

    if(val_0 == 0)
    {
        val_0 = 1;
    }

    if(val_1 == 0)
    {
        val_1 = 1;
    }

    pup.setX((pup.getX() / val_0) * (wallWidth / 2.0));
    pup.setZ((pup.getZ() / val_0) * (wallWidth / 2.0));

    pdown.setX((pdown.getX() / val_1) * (wallWidth / 2.0));
    pdown.setZ((pdown.getZ() / val_1) * (wallWidth / 2.0));

    double pup_meanX = (last_pup.getX() + pup.getX()) / 2.0;
    double pup_meanZ = (last_pup.getZ() + pup.getZ()) / 2.0;

    double pdown_meanX = (last_pdown.getX() + pdown.getX()) / 2.0;
    double pdown_meanZ = (last_pdown.getZ() + pdown.getZ()) / 2.0;

    pup.setX(pup_meanX);
    pup.setZ(pup_meanZ);

    pdown.setX(pdown_meanX);
    pdown.setZ(pdown_meanZ);

    /*Desloca os vértices na direção do vetor perpendicular*/
    if(centerVertexList.size() >= 3)
    {
        Vertex3D *v_0 = getVertex(currentIndex - 11);
        Vertex3D *v_1 = getVertex(currentIndex - 10);
        Vertex3D *v_2 = getVertex(currentIndex - 9);
        Vertex3D *v_3 = getVertex(currentIndex - 8);

        v_0->setX(c0->getX() + pup.getX());
        v_0->setZ(c0->getZ() + pup.getZ());
        v_1->setX(c0->getX() + pdown.getX());
        v_1->setZ(c0->getZ() + pdown.getZ());
        v_2->setX(c0->getX() + pup.getX());
        v_2->setZ(c0->getZ() + pup.getZ());
        v_3->setX(c0->getX() + pdown.getX());
        v_3->setZ(c0->getZ() + pdown.getZ());
    }

    v0->setX(c0->getX() + pup.getX());
    v0->setZ(c0->getZ() + pup.getZ());
    v1->setX(c0->getX() + pdown.getX());
    v1->setZ(c0->getZ() + pdown.getZ());
    v2->setX(c0->getX() + pup.getX());
    v2->setZ(c0->getZ() + pup.getZ());
    v3->setX(c0->getX() + pdown.getX());
    v3->setZ(c0->getZ() + pdown.getZ());

    v4->setX(c1->getX() + pup.getX());
    v4->setZ(c1->getZ() + pup.getZ());
    v5->setX(c1->getX() + pdown.getX());
    v5->setZ(c1->getZ() + pdown.getZ());
    v6->setX(c1->getX() + pup.getX());
    v6->setZ(c1->getZ() + pup.getZ());
    v7->setX(c1->getX() + pdown.getX());
    v7->setZ(c1->getZ() + pdown.getZ());

    last_pup = pup;
    last_pdown = pdown;
}

void Wall::addPoint(Point* point)
{
    Vertex3D *vertex = point->getVertex(0);
    centerVertexList.push_back(vertex);

    if(centerVertexList.size() >= 2)
    {
        Vertex3D *c1 = centerVertexList.at(centerVertexList.size() - 2);
        Vertex3D *c2 = centerVertexList.at(centerVertexList.size() - 1);

        Vertex3D *v0 = new Vertex3D(vertexId++, c1->getX() + last_pdown.getX(), 0.0, c1->getZ() + last_pdown.getZ());
        Vertex3D *v1 = new Vertex3D(vertexId++, c1->getX() + last_pup.getX(), 0.0, c1->getZ() + last_pup.getZ());
        Vertex3D *v2 = new Vertex3D(vertexId++, v0->getX(), wallHeight, v0->getZ());
        Vertex3D *v3 = new Vertex3D(vertexId++, v1->getX(), wallHeight, v1->getZ());

        Vertex3D *v4 = new Vertex3D(vertexId++, c2->getX() + last_pdown.getX(), 0.0, c2->getZ() + last_pdown.getZ());
        Vertex3D *v5 = new Vertex3D(vertexId++, c2->getX() + last_pup.getX(), 0.0, c2->getZ() + last_pup.getZ());
        Vertex3D *v6 = new Vertex3D(vertexId++, v4->getX(), wallHeight, v4->getZ());
        Vertex3D *v7 = new Vertex3D(vertexId++, v5->getX(), wallHeight, v5->getZ());

        addVertex(v0);
        addVertex(v1);
        addVertex(v2);
        addVertex(v3);

        addVertex(v4);
        addVertex(v5);
        addVertex(v6);
        addVertex(v7);

        addFace(new Quad(v0, v2, v3, v1));
        addFace(new Quad(v5, v7, v6, v4));
        addFace(new Quad(v0, v4, v6, v2));
        addFace(new Quad(v1, v3, v7, v5));
        addFace(new Quad(v2, v6, v7, v3));
        addFace(new Quad(v0, v1, v5, v4));

        updateVertexOrientation();

        double intervalX = abs((c1->getX() - c2->getX()));
        double intervalZ = abs((c1->getZ() - c2->getZ()));

        if(abs(intervalX) < wallWidth)
        {
            intervalX = wallWidth;
        }
        else if(abs(intervalZ) < wallWidth)
        {
            intervalZ = wallWidth;
        }

        Vertex3D center(-1, ((c1->getX() + c2->getX()) / 2.0), (wallHeight / 2.0), ((c1->getZ() + c2->getZ()) / 2.0));
        boundingBoxList.push_back(new BoundingBox(center, intervalX, intervalZ, wallHeight));
    }
}

void Wall::removeLastPoint()
{
    if(centerVertexList.size() > 0)
    {
        centerVertexList.pop_back();

        vector<Vertex3D*> *vertexList = getVertexList();

        if(centerVertexList.size() > 0)
        {
            vertexList->pop_back();
            vertexList->pop_back();
            vertexList->pop_back();
            vertexList->pop_back();
            vertexList->pop_back();
            vertexList->pop_back();
            vertexList->pop_back();
            vertexList->pop_back();

            vertexId -= 8;
        }

        vector<Primitive*>* faceList = getFaceList();

        if(centerVertexList.size() > 0)
        {
            faceList->pop_back();
            faceList->pop_back();
            faceList->pop_back();
            faceList->pop_back();
            faceList->pop_back();
            faceList->pop_back();
        }

        if(centerVertexList.size() == 0)
        {
            boundingBoxList.clear();
        }
        else
        {
            boundingBoxList.pop_back();
        }
    }
}

double Wall::getWallWidth()
{
    return wallWidth;
}

void Wall::increaseWallWidth()
{
    wallWidth += 0.1;
}

void Wall::decreaseWallWidth()
{
    if(wallWidth > 0.2)
    {
        wallWidth -= 0.1;
    }
}

double Wall::getWallHeight()
{
    return wallHeight;
}

void Wall::increaseWallHeight()
{
    wallHeight += 0.1;
}

void Wall::decreaseWallHeight()
{
    if(wallHeight > 0.2)
    {
        wallHeight -= 0.1;
    }
}

BoundingBox* Wall::getBoundingBox()
{
    return NULL;
}

std::vector<BoundingBox*>* Wall::getBoundingBoxList()
{
    return &boundingBoxList;
}
