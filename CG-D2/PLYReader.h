#ifndef PLYREADER_H_INCLUDED
#define PLYREADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <vector>

#include "PLYFile.h"

#include "Triangle.h"
#include "Quad.h"

class PLYReader
{
    private:
        // Calcula a normal de uma superfície do modelo 3D
        void calculateNormal(Vertex3D *v_0, Vertex3D *v_1, Vertex3D *v_2, Vertex3D *vn);
        // Calcula as normais das superfícies do modelo 3D
        void calculateNormalFaces(PLYFile* plyFile);

        // Obtém o mínimo e máximo dos eixos do modelo 3D
        void getMinMaxAxis(std::vector<Vertex3D*> *vertexList, double *minX, double *maxX, double *minY, double *maxY, double *minZ, double *maxZ);
        // Reescala o objeto para o intervalo [-1, 1] em todos os eixos
        void rescalingObject(PLYFile* plyFile);
    public:
        // Lê um arquivo PLY
        PLYFile* read_ply_file(std::string ply_filepath);
};

#endif // PLYREADER_H_INCLUDED
