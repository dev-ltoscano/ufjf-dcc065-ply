#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "Primitive.h"

class Line : public Primitive
{
    private:

    public:
        // Cria uma linha
        Line(Vertex3D* v0, Vertex3D* v1);

        // Obtém os vértices da linha
        Vertex3D* getV0();
        Vertex3D* getV1();
};

#endif // LINE_H_INCLUDED
