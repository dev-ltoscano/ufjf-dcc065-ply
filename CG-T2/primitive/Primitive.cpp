#include "Primitive.h"

using namespace std;

Primitive::~Primitive()
{
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        delete vertexList[i];
    }

    vertexList.clear();
}

void Primitive::addVertex(Vertex3D* vertex)
{
    this->vertexList.push_back(vertex);

    if(vertexList.size() == 3)
    {
        calculateNormal();
    }
}

Vertex3D* Primitive::getVertex(int idVertex)
{
    return this->vertexList.at(idVertex);
}

vector<Vertex3D*>* Primitive::getVertexList()
{
    return &this->vertexList;
}

int Primitive::getVertexCount()
{
    return this->vertexList.size();
}

void Primitive::calculateNormal()
{
    Vertex3D *v_0 = vertexList.at(0);
    Vertex3D *v_1 = vertexList.at(1);
    Vertex3D *v_2 = vertexList.at(2);
    double len;

    // Encontra vetor v1
    Vertex3D v1(-1, v_1->getX() - v_0->getX(), v_1->getY() - v_0->getY(), v_1->getZ() - v_0->getZ());

    // Encontra vetor v2
    Vertex3D v2(-1, v_2->getX() - v_0->getX(), v_2->getY() - v_0->getY(), v_2->getZ() - v_0->getZ());

    // Calculo do produto vetorial de v1 e v2
    normalVector.setX((v1.getY() * v2.getZ()) - (v1.getZ() * v2.getY()));
    normalVector.setY((v1.getZ() * v2.getX()) - (v1.getX() * v2.getZ()));
    normalVector.setZ((v1.getX() * v2.getY()) - (v1.getY() * v2.getX()));

    // normalizacao de n
    len = sqrt(pow(normalVector.getX(), 2.0) + pow(normalVector.getY(), 2.0) + pow(normalVector.getZ(), 2.0));

    normalVector.setX(normalVector.getX() / len);
    normalVector.setY(normalVector.getY() / len);
    normalVector.setZ(normalVector.getZ() / len);
}

void Primitive::drawPrimitive(bool wireframe)
{
    switch(vertexList.size())
    {
        case 1:
        {
            Vertex3D *v0 = vertexList.at(0);

            RGBColor color = getColor();
            glColor3d(color.r, color.g, color.b);

            glPointSize(8.0);

            glBegin(GL_POINTS);
                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
            glEnd();
            break;
        }
        case 2:
        {
            Vertex3D *v0 = vertexList.at(0);
            Vertex3D *v1 = vertexList.at(1);

            RGBColor color = getColor();
            glColor3d(color.r, color.g, color.b);

            glLineWidth(1.5);

            glBegin(GL_LINES);
                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
                glVertex3d(v1->getX(), v1->getY(), v1->getZ());
            glEnd();
            break;
        }
        case 3:
        {
            Vertex3D *v0 = vertexList.at(0);
            Vertex3D *v1 = vertexList.at(1);
            Vertex3D *v2 = vertexList.at(2);

            GLenum glPrimitive;

            if(wireframe)
            {
                glColor3d(1.0, 1.0, 1.0);
                glPrimitive = GL_LINE_LOOP;
            }
            else
            {
                RGBColor color = getColor();
                glColor3d(color.r, color.g, color.b);
                glPrimitive = GL_TRIANGLES;
            }

            glNormal3d(normalVector.getX(), normalVector.getY(), normalVector.getZ());

            glBegin(glPrimitive);
                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
                glVertex3d(v1->getX(), v1->getY(), v1->getZ());
                glVertex3d(v2->getX(), v2->getY(), v2->getZ());
            glEnd();
            break;
        }
        case 4:
        {
            Vertex3D *v0 = vertexList.at(0);
            Vertex3D *v1 = vertexList.at(1);
            Vertex3D *v2 = vertexList.at(2);
            Vertex3D *v3 = vertexList.at(3);

            GLenum glPrimitive;

            if(wireframe)
            {
                glPrimitive = GL_LINE_LOOP;
                glColor3d(1.0, 1.0, 1.0);
            }
            else
            {
                glPrimitive = GL_TRIANGLES;
                RGBColor color = getColor();
                glColor3d(color.r, color.g, color.b);
            }

            glNormal3d(normalVector.getX(), normalVector.getY(), normalVector.getZ());

            glBegin(glPrimitive);
                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
                glVertex3d(v1->getX(), v1->getY(), v1->getZ());
                glVertex3d(v2->getX(), v2->getY(), v2->getZ());
            glEnd();

            glBegin(glPrimitive);
                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
                glVertex3d(v2->getX(), v2->getY(), v2->getZ());
                glVertex3d(v3->getX(), v3->getY(), v3->getZ());
            glEnd();
            break;
        }
        default:
        {
            GLenum glPrimitive;

            if(wireframe)
            {
                glPrimitive = GL_LINE_LOOP;
                glColor3d(1.0, 1.0, 1.0);
            }
            else
            {
                glPrimitive = GL_POLYGON;
                RGBColor color = getColor();
                glColor3d(color.r, color.g, color.b);
            }

            glNormal3d(normalVector.getX(), normalVector.getY(), normalVector.getZ());

            glBegin(glPrimitive);
                for(unsigned int i = 0; i < vertexList.size(); i++)
                {
                    glVertex3d(vertexList[i]->getX(), vertexList[i]->getY(), vertexList[i]->getZ());
                }
            glEnd();
            break;
        }
    }
}

void Primitive::draw()
{
    drawPrimitive(false);
}

void Primitive::drawWireFrame()
{
    drawPrimitive(true);
}
