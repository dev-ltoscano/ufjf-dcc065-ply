#include "Collider.h"

Collider::Collider()
{
    // Instância a bounding box
    this->boundingBox = new BoundingBox();
}

BoundingBox* Collider::getBoundingBox(Vertex3D center, double width, double length, double height)
{
    // Atualiza o posicionamento da bounding box
    boundingBox->updateBox(center, width, length, height);
    return boundingBox;
}
