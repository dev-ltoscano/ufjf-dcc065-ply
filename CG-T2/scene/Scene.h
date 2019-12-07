#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "../object/ObjectGroup.h"

class Scene
{
    private:
        // Lista de grupos de objetos da cena
        std::vector<ObjectGroup*> objectGroupList;
    public:
        // Adiciona um novo grupo de objetos na cena
        void addNewObjectGroup(std::string groupName);
        void addObjectGroup(ObjectGroup *group);

        // Remove um grupo de objetos da cena
        void removeObjectGroup(int index);

        // Obtém um grupo de objetos da cena
        ObjectGroup* getObjectGroup(int index);
        // Obtém a lista de grupos de objetos da cena
        std::vector<ObjectGroup*>* getObjectGroupList();
        // Obtém o tamanho da lista de grupos de objetos da cena
        int objectGroupListSize();

        // Salva a cena em arquivo
        void saveScene(std::string filePath);
        // Carrega a cena a partir de arquivo
        void loadScene(std::string filePath);
};

#endif // SCENE_H_INCLUDED
