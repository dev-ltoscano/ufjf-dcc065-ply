#include "Drawable.h"

RGBColor Drawable::getColor()
{
    return this->rgbColor;
}

void Drawable::setColor(RGBColor rgbColor)
{
    this->rgbColor = rgbColor;
}

MaterialType Drawable::getMaterialType()
{
    return this->materialType;
}

void Drawable::setMaterialType(MaterialType materialType)
{
    this->materialType = materialType;
}
