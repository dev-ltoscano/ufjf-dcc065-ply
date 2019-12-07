#ifndef VERTEX3D_H_INCLUDED
#define VERTEX3D_H_INCLUDED

/*
*   Classe que representa um vértice 3D
*/
class Vertex3D
{
    private:
        int id;
        // Coordenadas 3D do vértice
        double x, y, z;
    public:
        // Cria um vértice na origem (0, 0, 0)
        Vertex3D();
        // Cria um vértice nas coordenadas (x, y, z)
        Vertex3D(int id, double x, double y, double z);

        // Obtém o Id do vértice
        int getId();

        // Obtém as coordenadas do vértice
        double getX();
        double getY();
        double getZ();

        // Define as coordenadas do vértice
        void setX(double x);
        void setY(double y);
        void setZ(double z);
};

#endif // VERTEX3D_H_INCLUDED
