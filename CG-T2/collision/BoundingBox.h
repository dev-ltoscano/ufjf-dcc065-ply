#ifndef BOUNDINGBOX_H_INCLUDED
#define BOUNDINGBOX_H_INCLUDED

#include "../primitive/Vertex3D.h"

class BoundingBox
{
    private:
        // Centro da bounding box
        Vertex3D center;
        // Largura, comprimento e altura da bounding box
        double width, length, height;
    public:
        // Construtores para a bounding box
        BoundingBox();
        BoundingBox(Vertex3D center, double width, double length, double height);
        // Atualiza a bounding box
        void updateBox(Vertex3D c0, double width, double length, double height);
        // Verifica se a bounding box colide com outra bounding box
        bool hit(BoundingBox *otherBox);
};

#endif // BOUNDINGBOX_H_INCLUDED
