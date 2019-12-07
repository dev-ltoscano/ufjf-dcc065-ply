#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <vector>

#include "Drawable.h"
#include "../primitive/RGBColor.h"
#include "../primitive/Line.h"

class Grid : public Drawable
{
    private:
        // Lista de linhas do grid
        std::vector<Line*> lineList;
    public:
        // Construtor do grid: Intervalo entre linhas e limites m�nimo e m�ximo de cada eixo
        Grid(double interval, double minX, double maxX, double minZ, double maxZ);
        ~Grid();

        // M�todos de desenho do grid
        void draw();
        void drawWireFrame();
};

#endif // GRID_H_INCLUDED
