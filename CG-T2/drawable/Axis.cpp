#include "Axis.h"

Axis::Axis()
{
    // Define a linha positiva do eixo X
    x_pos_line = new Line(new Vertex3D(0, 0.0, 0.0, 0.0), new Vertex3D(1, 1.0, 0.0, 0.0));
    x_pos_line->setColor(RGBColor(1.0, 0.0, 0.0));

    // Define a linha positiva do eixo Y
    y_pos_line = new Line(new Vertex3D(2, 0.0, 0.0, 0.0), new Vertex3D(3, 0.0, 1.0, 0.0));
    y_pos_line->setColor(RGBColor(0.0, 1.0, 0.0));

    // Define a linha positiva do eixo Z
    z_pos_line = new Line(new Vertex3D(4, 0.0, 0.0, 0.0), new Vertex3D(5, 0.0, 0.0, 1.0));
    z_pos_line->setColor(RGBColor(0.0, 0.0, 1.0));
}

Axis::~Axis()
{
    delete x_pos_line;
    delete y_pos_line;
    delete z_pos_line;
}

void Axis::draw()
{
    x_pos_line->draw();
    y_pos_line->draw();
    z_pos_line->draw();
}

void Axis::drawWireFrame()
{
    draw();
}
