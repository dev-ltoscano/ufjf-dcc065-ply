#ifndef PRIMITIVE_H_INCLUDED
#define PRIMITIVE_H_INCLUDED

#include <vector>
#include "Vertex3D.h"

/*
*   Classe que representa uma primitiva (Triângulo, quadrado)
*/
class Primitive
{
    private:
        // Lista de vértices da primitiva
        std::vector<Vertex3D*> vertexList;
    public:
        // Adiciona um vértice na lista de vértices da primitiva
        void addVertex(Vertex3D* vertex);
        // Obtém um vértice da lista de vértices da primitiva
        Vertex3D* getVertex(int idVertex);
        // Obtém a lista de vértices da primitiva
        std::vector<Vertex3D*>* getVertexList();
        // Obtém a quantidade de vértices da primitiva
        int getVertexCount();
};

#endif // PRIMITIVE_H_INCLUDED
