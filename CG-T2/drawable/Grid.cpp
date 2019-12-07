#include "Grid.h"
#include <iostream>

using namespace std;

Grid::Grid(double gridInterval, double minX, double maxX, double minZ, double maxZ)
{
    // Pontos iniciais
    double x0 = minX, y0 = 0.0, z0 = minZ;
    double x1 = minX, y1 = 0.0, z1 = maxZ;

    int vertexId = 0;
    Vertex3D *tmpV0, *tmpV1;
    Line *tmpLine;

    // Tamanho da grid de acordo com o intervalo entre as linhas da grid
    int gridSize = ((2 * maxX) / gridInterval) + 1;

    // Linhas paralelas ao eixo Z
    for(int i = 0; i <= gridSize; i++)
    {
        if(!(abs(x0) <= abs(1E-5)))
        {
            tmpV0 = new Vertex3D(vertexId++, x0, y0, z0);
            tmpV1 = new Vertex3D(vertexId++, x1, y1, z1);

            tmpLine = new Line(tmpV0, tmpV1);
            tmpLine->setColor(RGBColor(0.0, 0.0, 0.0));

            lineList.push_back(tmpLine);
        }
        else
        {
            tmpV0 = new Vertex3D(vertexId++, x0, y0, z0);
            tmpV1 = new Vertex3D(vertexId++, x1, y1, 0.0);

            tmpLine = new Line(tmpV0, tmpV1);
            tmpLine->setColor(RGBColor(0.0, 0.0, 0.0));

            lineList.push_back(tmpLine);
        }

        x0 += gridInterval;
        x1 += gridInterval;
    }

    x0 = minX, y0 = 0.0, z0 = minZ;
    x1 = maxX, y1 = 0.0, z1 = minZ;

    gridSize = ((2 * maxZ) / gridInterval) + 1;

    // Linhas paralelas ao eixo X
    for(int i = 0; i <= gridSize; i++)
    {
        if(!(abs(z0) <= abs(1E-5)))
        {
            tmpV0 = new Vertex3D(vertexId++, x0, y0, z0);
            tmpV1 = new Vertex3D(vertexId++, x1, y1, z1);

            tmpLine = new Line(tmpV0, tmpV1);
            tmpLine->setColor(RGBColor(0.0, 0.0, 0.0));

            lineList.push_back(tmpLine);
        }
        else
        {
            tmpV0 = new Vertex3D(vertexId++, x0, y0, z0);
            tmpV1 = new Vertex3D(vertexId++, 0.0, y1, z1);

            tmpLine = new Line(tmpV0, tmpV1);
            tmpLine->setColor(RGBColor(0.0, 0.0, 0.0));

            lineList.push_back(tmpLine);
        }

        z0 += gridInterval;
        z1 += gridInterval;
    }
}

Grid::~Grid()
{
    for(unsigned int i = 0; i < lineList.size(); i++)
    {
        delete lineList[i];
    }
}

void Grid::draw()
{
    for(unsigned int i = 0; i < lineList.size(); i++)
    {
        lineList[i]->draw();
    }
}

void Grid::drawWireFrame()
{
    draw();
}
