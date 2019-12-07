#include "Object.h"
#include <iostream>

using namespace std;

Object::Object()
{
    this->minX = 0.0;
    this->maxX = 0.0;

    this->minY = 0.0;
    this->maxY = 0.0;

    this->minZ = 0.0;
    this->maxZ = 0.0;

    this->width = 0.0;
    this->length = 0.0;
    this->height = 0.0;

    this->scaleX = 1.0;
    this->scaleY = 1.0;
    this->scaleZ = 1.0;

    this->rotationX = 0.0;
    this->rotationY = 0.0;
    this->rotationZ = 0.0;

    this->translationX = 0.0;
    this->translationY = 0.0;
    this->translationZ = 0.0;

    this->objIsDrawable = true;
    this->objIsCollisible = true;
}

Object::~Object()
{
    for(unsigned int i = 0; i < faceList.size(); i++)
    {
        delete faceList[i];
    }
}

Object* Object::clone()
{
    Object *objClone = new Object();

    Vertex3D *tmpVertex;

    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        tmpVertex = vertexList.at(i);
        objClone->addVertex(new Vertex3D(tmpVertex->getId(), tmpVertex->getX(), tmpVertex->getY(), tmpVertex->getZ()));
    }

    for(unsigned int i = 0; i < faceList.size(); i++)
    {
        vector<Vertex3D*> *faceVertexList = faceList.at(i)->getVertexList();
        Primitive *faceClone = new Primitive();

        for(unsigned int j = 0; j < faceVertexList->size(); j++)
        {
            faceClone->addVertex(objClone->getVertex(faceVertexList->at(j)->getId()));
        }

        objClone->addFace(faceClone);
    }

    objClone->minX = minX;
    objClone->maxX = maxX;
    objClone->minY = minY;
    objClone->maxY = maxY;
    objClone->minZ = minZ;
    objClone->maxZ = maxZ;

    objClone->width = width;
    objClone->length = length;
    objClone->height = height;

    objClone->scaleX = scaleX;
    objClone->scaleY = scaleY;
    objClone->scaleZ = scaleZ;

    objClone->rotationX = rotationX;
    objClone->rotationY = rotationY;
    objClone->rotationZ = rotationZ;

    objClone->translationX = translationX;
    objClone->translationY = translationY;
    objClone->translationZ = translationZ;

    objClone->objIsDrawable = objIsDrawable;
    objClone->objIsCollisible = objIsCollisible;

    return objClone;
}

void Object::getMinMaxAxis()
{
    if(vertexList.size() == 0)
    {
        return;
    }

    // Define os valores iniciais de mínimo/máximo para cada eixo
    minX = vertexList.at(0)->getX();
    maxX = vertexList.at(0)->getX();

    minY = vertexList.at(0)->getY();
    maxY = vertexList.at(0)->getY();

    minZ = vertexList.at(0)->getZ();
    maxZ = vertexList.at(0)->getZ();

    // Para todos os outros vértices
    for(unsigned int i = 1; i < vertexList.size(); i++)
    {
        // Verifica se é menor que o mínimo ou se é maior que o máximo no eixo-X
        if(vertexList.at(i)->getX() < minX)
        {
            // Altera o valor de mínimo no eixo-X
            minX = vertexList.at(i)->getX();
        }
        else if(vertexList.at(i)->getX() > maxX)
        {
            // Altera o valor de máximo no eixo-X
            maxX = vertexList.at(i)->getX();
        }

        // Verifica se é menor que o mínimo ou se é maior que o máximo no eixo-Y
        if(vertexList.at(i)->getY() < minY)
        {
            // Altera o valor de mínimo no eixo-Y
            minY = vertexList.at(i)->getY();
        }
        else if(vertexList.at(i)->getY() > maxY)
        {
            // Altera o valor de máximo no eixo-Y
            maxY = vertexList.at(i)->getY();
        }

        // Verifica se é menor que o mínimo ou se é maior que o máximo no eixo-Z
        if(vertexList.at(i)->getZ() < minZ)
        {
            // Altera o valor de mínimo no eixo-Z
            minZ = vertexList.at(i)->getZ();
        }
        else if(vertexList.at(i)->getZ() > maxZ)
        {
            // Altera o valor de máximo no eixo-Z
            maxZ = vertexList.at(i)->getZ();
        }
    }

    width = (maxX - minX);
    length = (maxZ - minZ);
    height = (maxY - minY);
}

double Object::convertDegreeToRadians(double degree)
{
    return (degree * M_PI / 180.0);
}

void Object::rescaling()
{
    getMinMaxAxis();

    // Obtém os intervalos de cada eixo
    double intervalX = (maxX - minX);
    double intervalY = (maxY - minY);
    double intervalZ = (maxZ - minZ);

    // Define o valor de escala do objeto como o maior intervalo
    double scaleObj = intervalX;

    if(scaleObj < intervalY)
    {
        scaleObj = intervalY;
    }

    if(scaleObj < intervalZ)
    {
        scaleObj = intervalZ;
    }

    double currX, currY, currZ;
    double newX, newY, newZ;

    // Escala o modelo para o intervalo [-1, 1]
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        currX = vertexList.at(i)->getX();
        currY = vertexList.at(i)->getY();
        currZ = vertexList.at(i)->getZ();

        newX = (2 * ((currX - minX) / scaleObj)) - 1;
        newY = (2 * ((currY - minY) / scaleObj)) - 1;
        newZ = (2 * ((currZ - minZ) / scaleObj)) - 1;

        vertexList.at(i)->setX(newX);
        vertexList.at(i)->setY(newY);
        vertexList.at(i)->setZ(newZ);
    }

    getMinMaxAxis();

    translate(1.0 - (width / 2.0), 1.0 - (height / 2.0), 1.0 - (length / 2.0));

    translationX = 0.0;
    translationY = 0.0;
    translationZ = 0.0;
}

void Object::rescaling(double scaleX, double scaleY, double scaleZ)
{
    double currX, currY, currZ;
    double newX, newY, newZ;

    // Escala o modelo para o intervalo [-1, 1]
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        currX = vertexList.at(i)->getX();
        currY = vertexList.at(i)->getY();
        currZ = vertexList.at(i)->getZ();

        newX = scaleX * currX;
        newY = scaleY * currY;
        newZ = scaleZ * currZ;

        vertexList.at(i)->setX(newX);
        vertexList.at(i)->setY(newY);
        vertexList.at(i)->setZ(newZ);
    }

    getMinMaxAxis();

    this->scaleX += scaleX;
    this->scaleY += scaleY;
    this->scaleZ += scaleZ;
}

void Object::centralize()
{
    translate(-translationX, -translationY, -translationZ);

    translationX = 0.0;
    translationY = 0.0;
    translationZ = 0.0;
}

void Object::translate(double dx, double dy, double dz)
{
    double currX, currY, currZ;

    // Centraliza o objeto na origem (0, 0, 0)
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        currX = vertexList.at(i)->getX();
        currY = vertexList.at(i)->getY();
        currZ = vertexList.at(i)->getZ();

        vertexList.at(i)->setX(currX + dx);
        vertexList.at(i)->setY(currY + dy);
        vertexList.at(i)->setZ(currZ + dz);
    }

    translationX += dx;
    translationY += dy;
    translationZ += dz;
}

void Object::rotateXAxis(double angle)
{
    double currX, currY, currZ;
    double newX, newY, newZ;

    double sinVal = sin(convertDegreeToRadians(angle));
    double cosVal = cos(convertDegreeToRadians(angle));

    // Escala o modelo para o intervalo [-1, 1]
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        currX = vertexList.at(i)->getX();
        currY = vertexList.at(i)->getY();
        currZ = vertexList.at(i)->getZ();

        newX = currX;
        newY = currY * cosVal - currZ * sinVal;
        newZ = currY * sinVal + currZ * cosVal;

        vertexList.at(i)->setX(newX);
        vertexList.at(i)->setY(newY);
        vertexList.at(i)->setZ(newZ);
    }

    rotationX = angle;
}

void Object::rotateYAxis(double angle)
{
    double currX, currY, currZ;
    double newX, newY, newZ;

    double sinVal = sin(convertDegreeToRadians(angle));
    double cosVal = cos(convertDegreeToRadians(angle));

    // Escala o modelo para o intervalo [-1, 1]
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        currX = vertexList.at(i)->getX();
        currY = vertexList.at(i)->getY();
        currZ = vertexList.at(i)->getZ();

        newX = currZ * sinVal + currX * cosVal;
        newY = currY;
        newZ = currZ * cosVal - currX * sinVal;

        vertexList.at(i)->setX(newX);
        vertexList.at(i)->setY(newY);
        vertexList.at(i)->setZ(newZ);
    }

    rotationY = angle;
}

void Object::rotateZAxis(double angle)
{
    double currX, currY, currZ;
    double newX, newY, newZ;

    double sinVal = sin(convertDegreeToRadians(angle));
    double cosVal = cos(convertDegreeToRadians(angle));

    // Escala o modelo para o intervalo [-1, 1]
    for(unsigned int i = 0; i < vertexList.size(); i++)
    {
        currX = vertexList.at(i)->getX();
        currY = vertexList.at(i)->getY();
        currZ = vertexList.at(i)->getZ();

        newX = currX * cosVal - currY * sinVal;
        newY = currX * sinVal + currY * cosVal;
        newZ = currZ;

        vertexList.at(i)->setX(newX);
        vertexList.at(i)->setY(newY);
        vertexList.at(i)->setZ(newZ);
    }

    rotationZ = angle;
}

void Object::addFace(Primitive *face)
{
    this->faceList.push_back(face);
}

Primitive* Object::getFace(int idFace)
{
    return this->faceList[idFace];
}

std::vector<Primitive*>* Object::getFaceList()
{
    return &this->faceList;
}

int Object::getFaceCount()
{
    return this->faceList.size();
}

void Object::addVertex(Vertex3D *vertex)
{
    this->vertexList.push_back(vertex);
}

Vertex3D* Object::getVertex(int idVertex)
{
    return this->vertexList[idVertex];
}

std::vector<Vertex3D*>* Object::getVertexList()
{
    return &this->vertexList;
}

int Object::getVertexCount()
{
    return this->vertexList.size();
}

Vertex3D Object::getCenter()
{
    return Vertex3D(-1, translationX, translationY, translationZ);
}

double Object::getWidth()
{
    return width;
}

double Object::getLength()
{
    return length;
}

double Object::getHeight()
{
    return height;
}

double Object::getScaleX()
{
    return scaleX;
}

double Object::getScaleY()
{
    return scaleY;
}

double Object::getScaleZ()
{
    return scaleZ;
}

double Object::getRotationX()
{
    return rotationX;
}

double Object::getRotationY()
{
    return rotationY;
}

double Object::getRotationZ()
{
    return rotationZ;
}

double Object::getTranslationX()
{
    return translationX;
}

double Object::getTranslationY()
{
    return translationY;
}

double Object::getTranslationZ()
{
    return translationZ;
}

void Object::setCenter(Vertex3D center)
{
    translationX = center.getX();
    translationY = center.getY();
    translationZ = center.getZ();
}

void Object::setWidth(double width)
{
    this->width = width;
}

void Object::setLength(double length)
{
    this->length = length;
}

void Object::setHeight(double height)
{
    this->height = height;
}

BoundingBox* Object::getCollider()
{
    return getBoundingBox(getCenter(), getWidth(), getLength(), getHeight());
}

void Object::setMaterialType(MaterialType materialType)
{
    Drawable::setMaterialType(materialType);

    for(unsigned int i = 0; i < faceList.size(); i++)
    {
        faceList[i]->setMaterialType(materialType);
    }
}

void Object::setColor(RGBColor color)
{
    Drawable::setColor(color);

    for(unsigned int i = 0; i < faceList.size(); i++)
    {
        faceList[i]->setColor(color);
    }
}

void Object::draw()
{
    switch(getMaterialType())
    {
        case PolishedBronze:
            setPolishedBronzeMaterial();
            break;
        case PolishedCopper:
            setPolishedCopperMaterial();
            break;
        case PolishedGold:
            setPolishedGoldMaterial();
            break;
        case PolishedSilver:
            setPolishedSilverMaterial();
            break;
        case Pewter:
            setPewterMaterial();
            break;
        case Emerald:
            setEmeraldMaterial();
            break;
        case Ruby:
            setRubyMaterial();
            break;
        case Turquoise:
            setTurquoiseMaterial();
            break;
        case BlackRubber:
            setBlackRubberMaterial();
            break;
        case Grass:
            setGrassMaterial();
            break;
        default:
            setPewterMaterial();
    }

    for(unsigned int i = 0; i < faceList.size(); i++)
    {
        faceList[i]->draw();
    }
}

void Object::drawWireFrame()
{
    for(unsigned int i = 0; i < faceList.size(); i++)
    {
        faceList[i]->drawWireFrame();
    }
}

bool Object::isDrawable()
{
    return this->objIsDrawable;
}

void Object::setDrawable(bool drawable)
{
    this->objIsDrawable = drawable;
}


bool Object::isCollisible()
{
    return this->objIsCollisible;
}

void Object::setCollisible(bool collisible)
{
    this->objIsCollisible = collisible;
}
