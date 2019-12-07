#ifndef AXIS_H_INCLUDED
#define AXIS_H_INCLUDED

#include "Drawable.h"

#include "../primitive/Vertex3D.h"
#include "../primitive/Line.h"

class Axis : public Drawable
{
    private:
        Line *x_pos_line, *y_pos_line, *z_pos_line;
    public:
        Axis();
        ~Axis();

        void draw();
        void drawWireFrame();
};

#endif // AXIS_H_INCLUDED
