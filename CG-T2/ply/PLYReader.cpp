#include "PLYReader.h"

using namespace std;

PLYObject* PLYReader::read_ply_file(string ply_filepath)
{
    // Abre o arquivo PLY
    ifstream plyFileStream(ply_filepath.c_str());

    // Verifica se o arquivo não foi aberto
    if(!plyFileStream.is_open())
    {
        // Lança exceção
        throw runtime_error("Não foi possível abrir o arquivo PLY");
    }

    // Variáveis temporárias para leitura do arquivo
    string tmpFileLine;
    string tmpLineValue;
    stringstream strStream;

    // Lê a primeira linha do arquivo
    getline(plyFileStream, tmpFileLine);
    strStream.str(tmpFileLine);
    strStream >> tmpLineValue;

    // Verifica se o arquivo não começa com a linha do "ply"
    if(tmpLineValue != "ply")
    {
        // Lança exceção
        throw runtime_error("Arquivo PLY inválido");
    }

    // Cria um novo objeto PLYFile
    PLYObject *plyObject = new PLYObject();

    // Lê o formato e a versão do arquivo PLY
    string fileType, fileVersion;
    getline(plyFileStream, tmpFileLine);
    strStream.clear();
    strStream.str(tmpFileLine);
    strStream >> tmpLineValue >> fileType >> fileVersion;

    // Verifica se o formato é ASCII
    if(fileType == "ascii")
    {
        // Caso seja, define o formato como ASCII e a versão do arquivo PLY
        plyObject->setFileFormat(PLYFormatVersion(ASCII, fileVersion));
    }
    else
    {
        // Caso contrário, lança exceção
        throw runtime_error("Formato de arquivo PLY não suportado");
    }

    // Faz a leitura linha a linha do cabeçalho do arquivo PLY
    while(getline(plyFileStream, tmpFileLine))
    {
        strStream.clear();
        strStream.str(tmpFileLine);
        strStream >> tmpLineValue;

        // Verifica se a linha é de comentário
        if(tmpLineValue == "comment")
        {
            // Caso seja, obtém o comentário
            getline(strStream, tmpLineValue);
            tmpLineValue.erase(tmpLineValue.begin());

            // Adiciona o comentário na lista de comentários do arquivo PLY
            plyObject->addComment(tmpLineValue);
        }
        else if(tmpLineValue == "element") // Verifica se a linha é de elemento
        {
            // Faz a leitura do elemento e da quantidade de elementos no arquivo PLY
            string elementName;
            int elementCount;
            strStream >> elementName >> elementCount;

            // Adiciona o elemento na lista de elementos do arquivo PLY
            plyObject->addElement(PLYElement(elementName, elementCount));
        }
        else if(tmpLineValue == "end_header") // Verifica se a linha é de fim de comentário
        {
            // Termina a leitura do cabeçalho do arquivo PLY
            break;
        }
    }

    // Obtém a lista de elementos do arquivo PLY
    list<PLYElement> elementList = plyObject->getElementList();

    // Para cada elemento do arquivo PLY
    for(auto it = elementList.begin(); it != elementList.end(); it++)
    {
        // Verifica se o elemento é o elemento de vértices do modelo 3D
        if((*it).elementName == "vertex")
        {
            // Obtém a quantidade de elementos de vértices do arquivo PLY
            int elementCount = (*it).elementCount;

            // Para cada elemento de vértice
            for(int i = 0; i < elementCount; i++)
            {
                // Faz a leitura da linha de um vértice
                getline(plyFileStream, tmpFileLine);

                // Faz a leitura das coordenadas x, y e z do vértice
                double x, y, z;
                strStream.clear();
                strStream.str(tmpFileLine);
                strStream >> x >> y >> z;

                // Adiciona o vértice na lista de vértices do modelo 3D
                plyObject->addVertex(new Vertex3D(i, x, y, z));
            }
        }
        else if((*it).elementName == "face") // Verifica se o elemento é o elemento de faces do modelo 3D
        {
            // Obtém a lista de vértices do modelo 3D
            vector<Vertex3D*>* vertexList = plyObject->getVertexList();
            // Obtém a quantidade de elementos de face do arquivo PLY
            int elementCount = (*it).elementCount;

            // Para cada elemento de face do arquivo PLY
            for(int i = 0; i < elementCount; i++)
            {
                // Faz a leitura da linha do elemento de face do arquivo PLY
                getline(plyFileStream, tmpFileLine);

                // Faz a leitura da quantidade de vértices que compõe a face
                int v_Count;
                strStream.clear();
                strStream.str(tmpFileLine);
                strStream >> v_Count;

                // Instancia um vetor de identificadores de vértices
                int v_Id_arr[v_Count];
                int v_Id;

                // Faz a leitura de cada identificador de vértice
                for(int j = 0; j < v_Count; j++)
                {
                    strStream >> v_Id;
                    v_Id_arr[j] = v_Id;
                }

                // Verifica se a quantidade de vértices é a de um triângulo
                if(v_Count == 3)
                {
                    // Obtém os vértices a partir dos índices
                    Vertex3D *v0 = vertexList->at(v_Id_arr[0]);
                    Vertex3D *v1 = vertexList->at(v_Id_arr[1]);
                    Vertex3D *v2 = vertexList->at(v_Id_arr[2]);

                    // Adiciona uma face triângular
                    plyObject->addFace(new Triangle(v0, v1, v2));
                }
                else if(v_Count == 4) // Verifica se a quantidade de vértices é a de um quadrado
                {
                    // Obtém os vértices a partir dos índices
                    Vertex3D *v0 = vertexList->at(v_Id_arr[0]);
                    Vertex3D *v1 = vertexList->at(v_Id_arr[1]);
                    Vertex3D *v2 = vertexList->at(v_Id_arr[2]);
                    Vertex3D *v3 = vertexList->at(v_Id_arr[3]);

                    // Adiciona uma face quadrada
                    plyObject->addFace(new Quad(v0, v1, v2, v3));
                }
                else if(v_Count == 5) // Verifica se a quantidade de vértices é a de um quadrado
                {
                    // Obtém os vértices a partir dos índices
                    Primitive *primitive = new Primitive();
                    primitive->addVertex(vertexList->at(v_Id_arr[0]));
                    primitive->addVertex(vertexList->at(v_Id_arr[1]));
                    primitive->addVertex(vertexList->at(v_Id_arr[2]));
                    primitive->addVertex(vertexList->at(v_Id_arr[3]));
                    primitive->addVertex(vertexList->at(v_Id_arr[4]));

                    plyObject->addFace(primitive);
                }
                else
                {
                    // Caso contrário, lança exceção
                    throw runtime_error("Primitiva não suportada");
                }
            }
        }
    }

    // Fecha o arquivo PLY
    plyFileStream.close();

    // Reescala o objeto para o intervalo [-1.0, 1.0] em todos os eixos
    plyObject->rescaling();

    // Retorna o arquivo PLY lido
    return plyObject;
}
