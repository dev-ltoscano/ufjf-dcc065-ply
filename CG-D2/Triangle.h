#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "Primitive.h"

/*
*   Classe que representa a primitiva triângulo
*/
class Triangle : public Primitive
{
    private:

    public:
        // Cria um triângulo com 3 vértices
        Triangle(Vertex3D* v0, Vertex3D* v1, Vertex3D* v2);

        // Obtém os vértices do triângulo
        Vertex3D* getV0();
        Vertex3D* getV1();
        Vertex3D* getV2();
};

#endif // TRIANGLE_H_INCLUDED
