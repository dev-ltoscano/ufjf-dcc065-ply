#ifndef MATERIALS_H_INCLUDED
#define MATERIALS_H_INCLUDED

#include <GL/glut.h>

GLfloat polished_bronze_ambient[] = {0.250000, 0.148000, 0.064750, 1.000000};
GLfloat polished_bronze_diffuse[] = {0.400000, 0.236800, 0.103600, 1.000000};
GLfloat polished_bronze_specular[] = {0.774597, 0.458561, 0.200621, 1.000000};
GLfloat polished_bronze_shininess[] = {76.800003};

GLfloat polished_copper_ambient[] = {0.229500, 0.088250, 0.027500, 1.000000};
GLfloat polished_copper_diffuse[] = {0.550800, 0.211800, 0.066000, 1.000000};
GLfloat polished_copper_specular[] = {0.580594, 0.223257, 0.069570, 1.000000};
GLfloat polished_copper_shininess[] = {51.200001};

GLfloat polished_gold_ambient[] = {0.247250, 0.224500, 0.064500, 1.000000};
GLfloat polished_gold_diffuse[] = {0.346150, 0.314300, 0.090300, 1.000000};
GLfloat polished_gold_specular[] = {0.797357, 0.723991, 0.208006, 1.000000};
GLfloat polished_gold_shininess[] = {83.199997};

GLfloat pewter_ambient[] = {0.105882, 0.058824, 0.113725, 1.000000};
GLfloat pewter_diffuse[] = {0.427451, 0.470588, 0.541176, 1.000000};
GLfloat pewter_specular[] = {0.333333, 0.333333, 0.521569, 1.000000};
GLfloat pewter_shininess[] = {9.846150};

GLfloat polished_silver_ambient[] = {0.231250, 0.231250, 0.231250, 1.000000};
GLfloat polished_silver_diffuse[] = {0.277500, 0.277500, 0.277500, 1.000000};
GLfloat polished_silver_specular[] = {0.773911, 0.773911, 0.773911, 1.000000};
GLfloat polished_silver_shininess[] = {89.599998};

GLfloat emerald_ambient[] = {0.021500, 0.174500, 0.021500, 0.550000};
GLfloat emerald_diffuse[] = {0.075680, 0.614240, 0.075680, 0.550000};
GLfloat emerald_specular[] = {0.633000, 0.727811, 0.633000, 0.550000};
GLfloat emerald_shininess[] = {76.800003};

GLfloat ruby_ambient[] = {0.174500, 0.011750, 0.011750, 0.550000};
GLfloat ruby_diffuse[] = {0.614240, 0.041360, 0.041360, 0.550000};
GLfloat ruby_specular[] = {0.727811, 0.626959, 0.626959, 0.550000};
GLfloat ruby_shininess[] = {76.800003};

GLfloat turquoise_ambient[] = {0.100000, 0.187250, 0.174500, 0.800000};
GLfloat turquoise_diffuse[] = {0.396000, 0.741510, 0.691020, 0.800000};
GLfloat turquoise_specular[] = {0.297254, 0.308290, 0.306678, 0.800000};
GLfloat turquoise_shininess[] = {12.800000};

GLfloat black_rubber_ambient[] = {0.020000, 0.020000, 0.020000, 1.000000};
GLfloat black_rubber_diffuse[] = {0.010000, 0.010000, 0.010000, 1.000000};
GLfloat black_rubber_specular[] = {0.400000, 0.400000, 0.400000, 1.000000};
GLfloat black_rubber_shininess[] = {10.000000};

void setMaterial(GLfloat* obj_front_ambient, GLfloat* obj_front_diffuse, GLfloat* obj_specular, GLfloat* obj_shininess)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, obj_front_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_front_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, obj_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, obj_shininess);
}

void setPolishedBronzeMaterial()
{
    setMaterial(polished_bronze_ambient, polished_bronze_diffuse, polished_bronze_specular, polished_bronze_shininess);
}

void setPolishedCopperMaterial()
{
    setMaterial(polished_copper_ambient, polished_copper_diffuse, polished_copper_specular, polished_copper_shininess);
}

void setPolishedGoldMaterial()
{
    setMaterial(polished_gold_ambient, polished_gold_diffuse, polished_gold_specular, polished_gold_shininess);
}

void setPewterMaterial()
{
    setMaterial(pewter_ambient, pewter_diffuse, pewter_specular, pewter_shininess);
}

void setPolishedSilverMaterial()
{
    setMaterial(polished_silver_ambient, polished_silver_diffuse, polished_silver_specular, polished_silver_shininess);
}

void setEmeraldMaterial()
{
    setMaterial(emerald_ambient, emerald_diffuse, emerald_specular, emerald_shininess);
}

void setRubyMaterial()
{
    setMaterial(ruby_ambient, ruby_diffuse, ruby_specular, ruby_shininess);
}

void setTurquoiseMaterial()
{
    setMaterial(turquoise_ambient, turquoise_diffuse, turquoise_specular, turquoise_shininess);
}

void setBlackRubberMaterial()
{
    setMaterial(black_rubber_ambient, black_rubber_diffuse, black_rubber_specular, black_rubber_shininess);
}

#endif // MATERIALS_H_INCLUDED
