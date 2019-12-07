#ifndef PLYFILE_H_INCLUDED
#define PLYFILE_H_INCLUDED

#include <string>
#include <list>
#include <vector>

#include "Vertex3D.h"
#include "Primitive.h"

// Enumeração dos tipos de arquivo PLY
enum PLYFileType
{
    ASCII_Type,
    BINARY_Type
};

// Estrutura que guarda o tipo e a versão de um arquivo PLY
struct PLYFileVersion
{
    PLYFileType fileType;
    std::string fileVersion;

    PLYFileVersion()
    {
        this->fileType = ASCII_Type;
        this->fileVersion = "1.0";
    }

    PLYFileVersion(PLYFileType fileType, std::string fileVersion)
    {
        this->fileType = fileType;
        this->fileVersion = fileVersion;
    }
};

// EStrutura que guarda um elemento e a quantidade desses elementos no arquivo PLY
struct PLYFileElement
{
    std::string elementName;
    int elementCount;

    PLYFileElement()
    {
        this->elementName = "";
        this->elementCount = 0;
    }

    PLYFileElement(std::string elementName, int elementCount)
    {
        this->elementName = elementName;
        this->elementCount = elementCount;
    }
};

/*
*   Classe que representa um arquivo PLY
*/
class PLYFile
{
    private:
        // Formato e versão do arquivo
        PLYFileVersion fileFormat;
        // Lista de comentários do arquivo
        std::list<std::string> commentList;
        // Lista de elementos do arquivo
        std::list<PLYFileElement> elementList;
        // Lista de vértices do modelo 3D
        std::vector<Vertex3D*> vertexList;
        // Lista de primitivas (Triângulos, quadrados) do modelo 3D
        std::vector<Primitive*> faceList;
        // Lista com normais das faces do modelo 3D
        std::vector<Vertex3D*> normalList;
        // Quantidade de vértices do modelo 3D
        int vertexCount = 0;
        // Quantidade de faces do modelo 3D
        int faceCount = 0;
    public:
        // Obtém o formato e a versão do arquivo
        PLYFileVersion getFileFormat();
        // Define o formato e a versão do arquivo
        void setFileFormat(PLYFileVersion fileFormat);

        // Adiciona um comentário na lista de comentários do arquivo
        void addComment(std::string comment);
        // Obtém a lista de comentários do arquivo
        std::list<std::string> getCommentList();

        // Adiciona um elemento na lista de elementos do arquivo
        void addElement(PLYFileElement element);
        // Obtém a lista de elementos do arquivo
        std::list<PLYFileElement> getElementList();

        // Adiciona um vértice na lista de vértices do modelo 3D
        void addVertex3D(Vertex3D* vertex);
        // Obtém a lista de vértices do modelo 3D
        std::vector<Vertex3D*>* getVertexList();
        // Obtém a quantidade de vértices do modelo 3D
        int getVertexCount();

        // Adiciona uma face na lista de faces do modelo 3D
        void addFace(Primitive* face);
        // Obtém a lista de faces do modelo 3D
        std::vector<Primitive*>* getFaceList();
        // Obtém a quantidade de faces do modelo 3D
        int getFaceCount();

        // Adiciona a normal de uma superfície na lista de normais do modelo 3D
        void addNormal(Vertex3D* normal);
        // Obtém a lista de normais do modelo 3D
        std::vector<Vertex3D*>* getNormalList();
};

#endif // PLYFILE_H_INCLUDED
