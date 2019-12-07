#ifndef MATERIALS_H_INCLUDED
#define MATERIALS_H_INCLUDED

#include <GL/glut.h>

// Tipos de material
enum MaterialType { PolishedBronze = 0, PolishedCopper = 1, PolishedGold = 2, PolishedSilver = 3, Pewter = 4, Emerald = 5, Ruby = 6, Turquoise = 7, BlackRubber = 8, Grass = 9 };

class Material
{
    private:
        // Definição dos materiais disponíveis
        GLfloat *polished_bronze_ambient = new GLfloat[4]{0.250000, 0.148000, 0.064750, 1.000000};
        GLfloat *polished_bronze_diffuse = new GLfloat[4]{0.400000, 0.236800, 0.103600, 1.000000};
        GLfloat *polished_bronze_specular = new GLfloat[4]{0.774597, 0.458561, 0.200621, 1.000000};
        GLfloat *polished_bronze_shininess = new GLfloat[1]{76.800003};

        GLfloat *polished_copper_ambient = new GLfloat[4]{0.229500, 0.088250, 0.027500, 1.000000};
        GLfloat *polished_copper_diffuse = new GLfloat[4]{0.550800, 0.211800, 0.066000, 1.000000};
        GLfloat *polished_copper_specular = new GLfloat[4]{0.580594, 0.223257, 0.069570, 1.000000};
        GLfloat *polished_copper_shininess = new GLfloat[1]{51.200001};

        GLfloat *polished_gold_ambient = new GLfloat[4]{0.247250, 0.224500, 0.064500, 1.000000};
        GLfloat *polished_gold_diffuse = new GLfloat[4]{0.346150, 0.314300, 0.090300, 1.000000};
        GLfloat *polished_gold_specular = new GLfloat[4]{0.797357, 0.723991, 0.208006, 1.000000};
        GLfloat *polished_gold_shininess = new GLfloat[1]{83.199997};

        GLfloat *pewter_ambient = new GLfloat[4]{0.105882, 0.058824, 0.113725, 1.000000};
        GLfloat *pewter_diffuse = new GLfloat[4]{0.427451, 0.470588, 0.541176, 1.000000};
        GLfloat *pewter_specular = new GLfloat[4]{0.333333, 0.333333, 0.521569, 1.000000};
        GLfloat *pewter_shininess = new GLfloat[1]{9.846150};

        GLfloat *polished_silver_ambient = new GLfloat[4]{0.231250, 0.231250, 0.231250, 1.000000};
        GLfloat *polished_silver_diffuse = new GLfloat[4]{0.277500, 0.277500, 0.277500, 1.000000};
        GLfloat *polished_silver_specular = new GLfloat[4]{0.773911, 0.773911, 0.773911, 1.000000};
        GLfloat *polished_silver_shininess = new GLfloat[1]{89.599998};

        GLfloat *emerald_ambient = new GLfloat[4]{0.021500, 0.174500, 0.021500, 0.550000};
        GLfloat *emerald_diffuse = new GLfloat[4]{0.075680, 0.614240, 0.075680, 0.550000};
        GLfloat *emerald_specular = new GLfloat[4]{0.633000, 0.727811, 0.633000, 0.550000};
        GLfloat *emerald_shininess = new GLfloat[1]{76.800003};

        GLfloat *ruby_ambient = new GLfloat[4]{0.174500, 0.011750, 0.011750, 0.550000};
        GLfloat *ruby_diffuse = new GLfloat[4]{0.614240, 0.041360, 0.041360, 0.550000};
        GLfloat *ruby_specular = new GLfloat[4]{0.727811, 0.626959, 0.626959, 0.550000};
        GLfloat *ruby_shininess = new GLfloat[1]{76.800003};

        GLfloat *turquoise_ambient = new GLfloat[4]{0.100000, 0.187250, 0.174500, 0.800000};
        GLfloat *turquoise_diffuse = new GLfloat[4]{0.396000, 0.741510, 0.691020, 0.800000};
        GLfloat *turquoise_specular = new GLfloat[4]{0.297254, 0.308290, 0.306678, 0.800000};
        GLfloat *turquoise_shininess = new GLfloat[1]{12.800000};

        GLfloat *black_rubber_ambient = new GLfloat[4]{0.020000, 0.020000, 0.020000, 1.000000};
        GLfloat *black_rubber_diffuse = new GLfloat[4]{0.010000, 0.010000, 0.010000, 1.000000};
        GLfloat *black_rubber_specular = new GLfloat[4]{0.400000, 0.400000, 0.400000, 1.000000};
        GLfloat *black_rubber_shininess = new GLfloat[1]{10.000000};

        GLfloat *grass_ambient = new GLfloat[4]{0.021500, 0.174500, 0.021500, 0.550000};
        GLfloat *grass_diffuse = new GLfloat[4]{0.075680, 0.614240, 0.075680, 0.550000};
        GLfloat *grass_specular = new GLfloat[4]{0.0, 0.0, 0.0, 0.0};
        GLfloat *grass_shininess = new GLfloat[1]{50.0};

        // Define o material do objeto
        void setObjectMaterial(GLfloat* obj_front_ambient, GLfloat* obj_front_diffuse, GLfloat* obj_specular, GLfloat* obj_shininess);
    public:
        ~Material();

        // Define cada tipo de material de objeto
        void setPolishedBronzeMaterial();
        void setPolishedCopperMaterial();
        void setPolishedGoldMaterial();
        void setPolishedSilverMaterial();
        void setPewterMaterial();
        void setEmeraldMaterial();
        void setRubyMaterial();
        void setTurquoiseMaterial();
        void setBlackRubberMaterial();
        void setGrassMaterial();
};

#endif // MATERIALS_H_INCLUDED
