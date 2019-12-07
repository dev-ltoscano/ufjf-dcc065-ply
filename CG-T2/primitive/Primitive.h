#ifndef PRIMITIVE_H_INCLUDED
#define PRIMITIVE_H_INCLUDED

#include <vector>
#include <cmath>
#include <GL/glut.h>

#include "../drawable/Drawable.h"
#include "Vertex3D.h"

/*
*   Classe que representa uma primitiva (Triângulo, quadrado, etc)
*/
class Primitive : public Drawable
{
    private:
        // Lista de vértices da primitiva
        std::vector<Vertex3D*> vertexList;
        // Vetor normal da primitiva
        Vertex3D normalVector;

        // Calcula o vetor normal da primitiva
        void calculateNormal();
        // Desenha a primitiva
        void drawPrimitive(bool wireframe);
    public:
        virtual ~Primitive();

        // Adiciona um vértice na lista de vértices da primitiva
        void addVertex(Vertex3D* vertex);
        // Obtém um vértice da lista de vértices da primitiva
        Vertex3D* getVertex(int idVertex);
        // Obtém a lista de vértices da primitiva
        std::vector<Vertex3D*>* getVertexList();
        // Obtém a quantidade de vértices da primitiva
        int getVertexCount();

        // Métodos de desenho da primitiva
        void draw();
        void drawWireFrame();
};

#endif // PRIMITIVE_H_INCLUDED
