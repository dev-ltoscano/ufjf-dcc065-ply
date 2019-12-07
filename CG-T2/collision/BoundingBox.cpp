#include "BoundingBox.h"
#include <iostream>

using namespace std;

BoundingBox::BoundingBox()
{
    this->width = 0.0;
    this->length = 0.0;
    this->height = 0.0;
}

BoundingBox::BoundingBox(Vertex3D center, double width, double length, double height)
{
    this->center = center;
    this->width = width;
    this->length = length;
    this->height = height;
}

void BoundingBox::updateBox(Vertex3D center, double width, double length, double height)
{
    this->center = center;
    this->width = width;
    this->length = length;
    this->height = height;
}

bool BoundingBox::hit(BoundingBox *otherBox)
{
    // Metade das dimensões em cada eixo da bounding box atual
    double AmiddleWidth = width / 2.0;
    double AmiddleLength = length / 2.0;
    double AmiddleHeight = height / 2.0;

    // Valor mínimo e máximo no eixo X da bounding box atual
    double AminX = center.getX() - AmiddleWidth;
    double AmaxX = center.getX() + AmiddleWidth;

    // Valor mínimo e máximo no eixo Z da bounding box atual
    double AminZ = center.getZ() - AmiddleLength;
    double AmaxZ = center.getZ() + AmiddleLength;

    // Valor mínimo e máximo no eixo Y da bounding box atual
    double AminY = center.getY() - AmiddleHeight;
    double AmaxY = center.getY() + AmiddleHeight;

    // Metade das dimensões em cada eixo da outra bounding box
    double BmiddleWidth = otherBox->width / 2.0;
    double BmiddleLength = otherBox->length / 2.0;
    double BmiddleHeight = otherBox->height / 2.0;

    // Valor mínimo e máximo no eixo X da outra bounding box
    double BminX = otherBox->center.getX() - BmiddleWidth;
    double BmaxX = otherBox->center.getX() + BmiddleWidth;

    // Valor mínimo e máximo no eixo Z da outra bounding box
    double BminZ = otherBox->center.getZ() - BmiddleLength;
    double BmaxZ = otherBox->center.getZ() + BmiddleLength;

    // Valor mínimo e máximo no eixo Y da outra bounding box
    double BminY = otherBox->center.getY() - BmiddleHeight;
    double BmaxY = otherBox->center.getY() + BmiddleHeight;

    // Verifica se os limites da bounding box ultrapassam o da outra
    return (((AminX < BmaxX) && (AmaxX > BminX))
            && ((AminY < BmaxY) && (AmaxY > BminY))
            && ((AminZ < BmaxZ) && (AmaxZ > BminZ)));
}
