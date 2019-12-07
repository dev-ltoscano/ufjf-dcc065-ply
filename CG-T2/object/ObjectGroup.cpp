#include "ObjectGroup.h"

using namespace std;

ObjectGroup::ObjectGroup(string groupName)
{
    this->groupName = groupName;
    this->groupMaterialType = Pewter;
    this->addObject(new Wall(), true, false);
}

string ObjectGroup::getGroupName()
{
    return groupName;
}

MaterialType ObjectGroup::getGroupMaterialType()
{
    return groupMaterialType;
}

void ObjectGroup::addObject(Object *obj, bool isDrawable, bool isCollisible)
{
    objectList.push_back(obj);

    obj->setMaterialType(groupMaterialType);

    if(isDrawable)
    {
        obj->setDrawable(true);
        drawableList.push_back(obj);
    }
    else
    {
        obj->setDrawable(false);
    }

    if(isCollisible)
    {
        obj->setCollisible(true);
        colliderList.push_back(obj);
    }
    else
    {
        obj->setCollisible(false);
    }
}

Object* ObjectGroup::getObject(int index)
{
    return objectList.at(index);
}

vector<Object*>* ObjectGroup::getObjectList()
{
    return &objectList;
}

int ObjectGroup::objectListSize()
{
    return objectList.size();
}

vector<Drawable*>* ObjectGroup::getDrawableList()
{
    return &drawableList;
}

vector<Collider*>* ObjectGroup::getColliderList()
{
    return &colliderList;
}

vector<BoundingBox*>* ObjectGroup::getWallBoundingBoxList()
{
    return ((Wall*)objectList.at(0))->getBoundingBoxList();
}

void ObjectGroup::addWallPoint(Point *point)
{
    ((Wall*)objectList.at(0))->addPoint(point);
    pointList.push_back(point);
}

void ObjectGroup::removeLastWallPoint()
{
    ((Wall*)objectList.at(0))->removeLastPoint();

    if(pointList.size() > 0)
    {
        pointList.pop_back();
    }
}

std::vector<Point*>* ObjectGroup::getWallPointList()
{
    return &pointList;
}

int ObjectGroup::wallPointListSize()
{
    return pointList.size();
}

double ObjectGroup::getWallWidth()
{
    return ((Wall*)objectList.at(0))->getWallWidth();
}

void ObjectGroup::increaseWallWidth()
{
    ((Wall*)objectList.at(0))->increaseWallWidth();
}

void ObjectGroup::decreaseWallWidth()
{
    ((Wall*)objectList.at(0))->decreaseWallWidth();
}

double ObjectGroup::getWallHeight()
{
    return ((Wall*)objectList.at(0))->getWallHeight();
}

void ObjectGroup::increaseWallHeight()
{
    ((Wall*)objectList.at(0))->increaseWallHeight();
}

void ObjectGroup::decreaseWallHeight()
{
    ((Wall*)objectList.at(0))->decreaseWallHeight();
}

void ObjectGroup::setMaterialGroup(MaterialType materialType)
{
    drawableList[0]->setMaterialType(materialType);

    for(unsigned int i = 1; i < drawableList.size(); i++)
    {
        drawableList[i]->setMaterialType(materialType);
    }

    groupMaterialType = materialType;
}

void ObjectGroup::clearGroup()
{
    objectList.clear();
    drawableList.clear();
    colliderList.clear();
    pointList.clear();

    addObject(new Wall(), true, false);
}
