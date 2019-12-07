#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include "../primitive/RGBColor.h"
#include "../material/Material.h"

class Drawable : public Material
{
    private:
        // Cor do objeto
        RGBColor rgbColor;
        // Tipo de material do objeto
        MaterialType materialType;
    public:
        // Obtém a cor do objeto
        virtual RGBColor getColor();
        // Define a cor do objeto
        virtual void setColor(RGBColor rgbColor);

        // Obtém o material do objeto
        virtual MaterialType getMaterialType();
        // Define o material do objeto
        virtual void setMaterialType(MaterialType materialType);

        // Métodos para desenho do objeto
        virtual void draw() = 0;
        virtual void drawWireFrame() = 0;
};

#endif // DRAWABLE_H_INCLUDED
