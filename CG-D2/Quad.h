#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "Primitive.h"

/*
*   Classe que representa a primitiva quadrado
*/
class Quad : public Primitive
{
    private:

    public:
        // Cria um quadrado com 4 vértices
        Quad(Vertex3D* v0, Vertex3D* v1, Vertex3D* v2, Vertex3D* v3);

        // Obtém os vértices do quadrado
        Vertex3D* getV0();
        Vertex3D* getV1();
        Vertex3D* getV2();
        Vertex3D* getV3();
};

#endif // QUAD_H_INCLUDED
