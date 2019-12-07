#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <vector>
#include <cmath>

#include "../drawable/Drawable.h"
#include "../collision/Collider.h"

#include "../primitive/Vertex3D.h"
#include "../primitive/Primitive.h"
#include "../primitive/RGBColor.h"

#define M_PI    3.14159265359

class Object : public Drawable, public Collider
{
    private:
        std::vector<Vertex3D*> vertexList;
        std::vector<Primitive*> faceList;

        double minX, maxX, minY, maxY, minZ, maxZ;
        double width, length, height;

        double scaleX, scaleY, scaleZ;
        double rotationX, rotationY, rotationZ;
        double translationX, translationY, translationZ;

        bool objIsDrawable, objIsCollisible;

        void getMinMaxAxis();
        double convertDegreeToRadians(double degree);
    public:
        Object();
        ~Object();

        Object* clone();

        void rescaling();
        void rescaling(double scaleX, double scaleY, double scaleZ);

        void centralize();
        void translate(double dx, double dy, double dz);

        void rotateXAxis(double angle);
        void rotateYAxis(double angle);
        void rotateZAxis(double angle);

        void addFace(Primitive *face);
        Primitive* getFace(int idFace);
        std::vector<Primitive*>* getFaceList();
        int getFaceCount();

        void addVertex(Vertex3D *vertex);
        Vertex3D* getVertex(int idVertex);
        std::vector<Vertex3D*>* getVertexList();
        int getVertexCount();

        Vertex3D getCenter();
        double getWidth();
        double getLength();
        double getHeight();

        double getScaleX();
        double getScaleY();
        double getScaleZ();

        double getRotationX();
        double getRotationY();
        double getRotationZ();

        double getTranslationX();
        double getTranslationY();
        double getTranslationZ();

        void setCenter(Vertex3D center);
        void setWidth(double width);
        void setLength(double length);
        void setHeight(double height);

        BoundingBox* getCollider();

        void setMaterialType(MaterialType materialType);
        void setColor(RGBColor color);

        void draw();
        void drawWireFrame();

        bool isDrawable();
        void setDrawable(bool drawable);

        bool isCollisible();
        void setCollisible(bool collisible);
};

#endif // OBJECT_H_INCLUDED
