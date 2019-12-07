#include "Scene.h"

using namespace std;

void Scene::addNewObjectGroup(string groupName)
{
    objectGroupList.push_back(new ObjectGroup(groupName));
}

void Scene::addObjectGroup(ObjectGroup *group)
{
    objectGroupList.push_back(group);
}

void Scene::removeObjectGroup(int index)
{
    objectGroupList.erase(objectGroupList.begin() + index);
}

ObjectGroup* Scene::getObjectGroup(int index)
{
    return objectGroupList.at(index);
}

vector<ObjectGroup*>* Scene::getObjectGroupList()
{
    return &objectGroupList;
}

int Scene::objectGroupListSize()
{
    return objectGroupList.size();
}

void Scene::saveScene(string filePath)
{
    ofstream sceneFile(filePath.c_str());

    if (!sceneFile.is_open())
    {
        cout << ">>>>> ERRO: Não foi possível criar o arquivo " << filePath << endl;
        return;
    }

    sceneFile << std::fixed << std::setprecision(6);

    ObjectGroup *tmpObjectGroup;
    vector<Object*> *tmpObjectList;
    Object *tmpObject;
    vector<Vertex3D*> *tmpVertexList;
    Vertex3D* tmpVertex;
    vector<Primitive*> *tmpFaceList;
    Primitive* tmpFace;
    vector<Point*> *tmpPointList;
    Point* tmpPoint;

    // Escreve a quantidade de grupos
    sceneFile << objectGroupList.size() << endl;

    for(unsigned int i = 0; i < objectGroupList.size(); i++)
    {
        tmpObjectGroup = objectGroupList[i];

        // Escreve o Id do grupo
        sceneFile << tmpObjectGroup->getGroupName() << endl;
        // Escreve o material do grupo
        sceneFile << tmpObjectGroup->getGroupMaterialType() << endl;

        // Escreve a quantidade de pontos do grupo
        tmpPointList = tmpObjectGroup->getWallPointList();
        sceneFile << tmpPointList->size() << endl;

        // Escreve todos os pontos do grupo
        for(unsigned int k = 0; k < tmpPointList->size(); k++)
        {
            tmpPoint = tmpPointList->at(k);
            tmpVertex = tmpPoint->getV0();
            sceneFile << tmpVertex->getId() << " " << tmpVertex->getX() << " " << tmpVertex->getY() << " " << tmpVertex->getZ() << endl;
        }

        // Escreve a quantidade de objetos do grupo
        tmpObjectList = tmpObjectGroup->getObjectList();
        sceneFile << tmpObjectList->size() - 1 << endl;

        // Escreve todos os objetos do grupo
        for(unsigned int j = 1; j < tmpObjectList->size(); j++)
        {
            tmpObject = tmpObjectList->at(j);
            tmpVertexList = tmpObject->getVertexList();

            // Escreve se o arquivo é desenhável e se tem colisão
            sceneFile << tmpObject->isDrawable() << " " << tmpObject->isCollisible() << endl;

            // Escreve o centro do objeto
            Vertex3D objCenter = tmpObject->getCenter();
            sceneFile << objCenter.getX() << " " << objCenter.getY() << " " << objCenter.getZ() << endl;

            // Escreve a quantidade de vértices do objeto
            sceneFile << tmpVertexList->size() << endl;

            // Escreve todos os vértices do objeto
            for(unsigned int k = 0; k < tmpVertexList->size(); k++)
            {
                tmpVertex = tmpVertexList->at(k);
                sceneFile << tmpVertex->getId() << " " << tmpVertex->getX() << " " << tmpVertex->getY() << " " << tmpVertex->getZ() << endl;
            }

            // Escreve a quantidade de faces do objeto
            tmpFaceList = tmpObject->getFaceList();
            sceneFile << tmpFaceList->size() << endl;

            // Escreve todas as faces do objeto
            for(unsigned int k = 0; k < tmpFaceList->size(); k++)
            {
                tmpFace = tmpFaceList->at(k);
                tmpVertexList = tmpFace->getVertexList();

                // Escreve a quantidade de vértices que compõe a face
                sceneFile << tmpVertexList->size() << " ";

                // Escreve os IDs dos vértices que compõem a face
                for(unsigned int w = 0; w < tmpVertexList->size(); w++)
                {
                    tmpVertex = tmpVertexList->at(w);

                    if(w < (tmpVertexList->size() - 1))
                    {
                        sceneFile << tmpVertex->getId() << " ";
                    }
                    else
                    {
                        sceneFile << tmpVertex->getId() << endl;
                    }
                }
            }
        }

        sceneFile << endl;
    }

    sceneFile.close();
    cout << ">>>>> Cenário salvo!" << endl;
}

void Scene::loadScene(std::string filePath)
{
    ifstream sceneFile(filePath.c_str());

    if (!sceneFile.is_open())
    {
        cout << ">>>>> ERRO: Não foi possível abrir o arquivo " << filePath << endl;
        return;
    }

    objectGroupList.clear();

    string tmpLine;
    istringstream lineStream;

    int objectGroupSize;
    lineStream.clear();
    getline(sceneFile, tmpLine);
    lineStream.str(tmpLine);
    lineStream >> objectGroupSize;

    for(int i = 0; i < objectGroupSize; i++)
    {
        string groupName;
        lineStream.clear();
        getline(sceneFile, tmpLine);
        lineStream.str(tmpLine);
        lineStream >> groupName;

        ObjectGroup *objGroup = new ObjectGroup(groupName);

        int groupMaterialType;
        lineStream.clear();
        getline(sceneFile, tmpLine);
        lineStream.str(tmpLine);
        lineStream >> groupMaterialType;

        MaterialType matType = static_cast<MaterialType>(groupMaterialType);
        objGroup->setMaterialGroup(matType);

        int pointListSize;
        lineStream.clear();
        getline(sceneFile, tmpLine);
        lineStream.str(tmpLine);
        lineStream >> pointListSize;

        for(int j = 0 ; j < pointListSize; j++)
        {
            int vertexId;
            double x, y, z;

            lineStream.clear();
            getline(sceneFile, tmpLine);
            lineStream.str(tmpLine);
            lineStream >> vertexId >> x >> y >> z;

            objGroup->addWallPoint(new Point(new Vertex3D(vertexId, x, y, z)));
        }

        int objectSize;
        lineStream.clear();
        getline(sceneFile, tmpLine);
        lineStream.str(tmpLine);
        lineStream >> objectSize;

        for(int j = 0 ; j < objectSize; j++)
        {
            Object *obj = new Object();

            bool objDrawable, objCollisible;
            lineStream.clear();
            getline(sceneFile, tmpLine);
            lineStream.str(tmpLine);
            lineStream >> objDrawable >> objCollisible;

            obj->setDrawable(objDrawable);
            obj->setCollisible(objCollisible);

            double objCenterX, objCenterY, objCenterZ;
            lineStream.clear();
            getline(sceneFile, tmpLine);
            lineStream.str(tmpLine);
            lineStream >> objCenterX >> objCenterY >> objCenterZ;

            obj->setCenter(Vertex3D(-1, objCenterX, objCenterY, objCenterZ));

            int vertexListSize;
            lineStream.clear();
            getline(sceneFile, tmpLine);
            lineStream.str(tmpLine);
            lineStream >> vertexListSize;

            for(int k = 0 ; k < vertexListSize; k++)
            {
                int vertexId;
                double x, y, z;

                lineStream.clear();
                getline(sceneFile, tmpLine);
                lineStream.str(tmpLine);
                lineStream >> vertexId >> x >> y >> z;

                obj->addVertex(new Vertex3D(vertexId, x, y, z));
            }

            int faceListSize;
            lineStream.clear();
            getline(sceneFile, tmpLine);
            lineStream.str(tmpLine);
            lineStream >> faceListSize;

            for(int k = 0 ; k < faceListSize; k++)
            {
                int vertexCount;
                lineStream.clear();
                getline(sceneFile, tmpLine);
                lineStream.str(tmpLine);
                lineStream >> vertexCount;

                int vertexIdArray[vertexCount];

                for(int w = 0 ; w < vertexCount; w++)
                {
                    lineStream >> vertexIdArray[w];
                }

                Primitive *face = new Primitive();

                for(int w = 0 ; w < vertexCount; w++)
                {
                    face->addVertex(obj->getVertex(vertexIdArray[w]));
                }

                obj->addFace(face);
            }

            objGroup->addObject(obj, obj->isDrawable(), obj->isCollisible());
        }

        addObjectGroup(objGroup);
        getline(sceneFile, tmpLine);
    }

    sceneFile.close();
    cout << ">>>>> Cenário carregado!" << endl;
}
