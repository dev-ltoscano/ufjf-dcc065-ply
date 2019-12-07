#include "Material.h"

Material::~Material()
{
    delete polished_bronze_ambient;
    delete polished_bronze_diffuse;
    delete polished_bronze_specular;
    delete polished_bronze_shininess;

    delete polished_copper_ambient;
    delete polished_copper_diffuse;
    delete polished_copper_specular;
    delete polished_copper_shininess;

    delete polished_gold_ambient;
    delete polished_gold_diffuse;
    delete polished_gold_specular;
    delete polished_gold_shininess;

    delete pewter_ambient;
    delete pewter_diffuse;
    delete pewter_specular;
    delete pewter_shininess;

    delete polished_silver_ambient;
    delete polished_silver_diffuse;
    delete polished_silver_specular;
    delete polished_silver_shininess;

    delete emerald_ambient;
    delete emerald_diffuse;
    delete emerald_specular;
    delete emerald_shininess;

    delete ruby_ambient;
    delete ruby_diffuse;
    delete ruby_specular;
    delete ruby_shininess;

    delete turquoise_ambient;
    delete turquoise_diffuse;
    delete turquoise_specular;
    delete turquoise_shininess;

    delete black_rubber_ambient;
    delete black_rubber_diffuse;
    delete black_rubber_specular;
    delete black_rubber_shininess;

    delete grass_ambient;
    delete grass_diffuse;
    delete grass_specular;
    delete grass_shininess;
}

void Material::setObjectMaterial(GLfloat* obj_front_ambient, GLfloat* obj_front_diffuse, GLfloat* obj_specular, GLfloat* obj_shininess)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, obj_front_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_front_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, obj_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, obj_shininess);
}

void Material::setPolishedBronzeMaterial()
{
    setObjectMaterial(polished_bronze_ambient, polished_bronze_diffuse, polished_bronze_specular, polished_bronze_shininess);
}

void Material::setPolishedCopperMaterial()
{
    setObjectMaterial(polished_copper_ambient, polished_copper_diffuse, polished_copper_specular, polished_copper_shininess);
}

void Material::setPolishedGoldMaterial()
{
    setObjectMaterial(polished_gold_ambient, polished_gold_diffuse, polished_gold_specular, polished_gold_shininess);
}

void Material::setPolishedSilverMaterial()
{
    setObjectMaterial(polished_silver_ambient, polished_silver_diffuse, polished_silver_specular, polished_silver_shininess);
}

void Material::setPewterMaterial()
{
    setObjectMaterial(pewter_ambient, pewter_diffuse, pewter_specular, pewter_shininess);
}

void Material::setEmeraldMaterial()
{
    setObjectMaterial(emerald_ambient, emerald_diffuse, emerald_specular, emerald_shininess);
}

void Material::setRubyMaterial()
{
    setObjectMaterial(ruby_ambient, ruby_diffuse, ruby_specular, ruby_shininess);
}

void Material::setTurquoiseMaterial()
{
    setObjectMaterial(turquoise_ambient, turquoise_diffuse, turquoise_specular, turquoise_shininess);
}

void Material::setBlackRubberMaterial()
{
    setObjectMaterial(black_rubber_ambient, black_rubber_diffuse, black_rubber_specular, black_rubber_shininess);
}

void Material::setGrassMaterial()
{
    setObjectMaterial(grass_ambient, grass_diffuse, grass_specular, grass_shininess);
}
