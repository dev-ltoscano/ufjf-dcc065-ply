#ifndef PLYFILE_H_INCLUDED
#define PLYFILE_H_INCLUDED

#include <string>
#include <list>

#include "../object/Object.h"

// Enumeração dos tipos de arquivo PLY
enum PLYType
{
    ASCII,
    BINARY
};

// Estrutura que guarda o tipo e a versão de um arquivo PLY
struct PLYFormatVersion
{
    PLYType plyType;
    std::string plyVersion;

    PLYFormatVersion()
    {
        this->plyType = ASCII;
        this->plyVersion = "1.0";
    }

    PLYFormatVersion(PLYType plyType, std::string plyVersion)
    {
        this->plyType = plyType;
        this->plyVersion = plyVersion;
    }
};

// Estrutura que guarda um elemento e a quantidade desses elementos no arquivo PLY
struct PLYElement
{
    std::string elementName;
    int elementCount;

    PLYElement()
    {
        this->elementName = "";
        this->elementCount = 0;
    }

    PLYElement(std::string elementName, int elementCount)
    {
        this->elementName = elementName;
        this->elementCount = elementCount;
    }
};

/*
*   Classe que representa um arquivo PLY
*/
class PLYObject : public Object
{
    private:
        // Formato e versão do arquivo
        PLYFormatVersion fileFormat;
        // Lista de comentários do arquivo
        std::list<std::string> commentList;
        // Lista de elementos do arquivo
        std::list<PLYElement> elementList;
    public:
        // Obtém o formato e a versão do arquivo
        PLYFormatVersion getFileFormat();
        // Define o formato e a versão do arquivo
        void setFileFormat(PLYFormatVersion format);

        // Adiciona um comentário na lista de comentários do arquivo
        void addComment(std::string comment);
        // Obtém a lista de comentários do arquivo
        std::list<std::string> getCommentList();

        // Adiciona um elemento na lista de elementos do arquivo
        void addElement(PLYElement element);
        // Obtém a lista de elementos do arquivo
        std::list<PLYElement> getElementList();
};

#endif // PLYFILE_H_INCLUDED
