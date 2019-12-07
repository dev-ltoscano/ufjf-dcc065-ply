#ifndef RGBCOLOR_H_INCLUDED
#define RGBCOLOR_H_INCLUDED

/*
*   Estrutura para uma cor em RGB
*/
struct RGBColor
{
    double r, g, b;

    RGBColor()
    {
        this->r = 1.0;
        this->g = 0.0;
        this->b = 1.0;
    }

    RGBColor(double r, double g, double b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif // RGBCOLOR_H_INCLUDED
