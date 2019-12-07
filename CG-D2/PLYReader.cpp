#include "PLYReader.h"

using namespace std;

void PLYReader::calculateNormal(Vertex3D *v_0, Vertex3D *v_1, Vertex3D *v_2, Vertex3D *vn)
{
    double len;

    // Encontra vetor v1
    Vertex3D v1(v_1->getX() - v_0->getX(), v_1->getY() - v_0->getY(), v_1->getZ() - v_0->getZ());

    // Encontra vetor v2
    Vertex3D v2(v_2->getX() - v_0->getX(), v_2->getY() - v_0->getY(), v_2->getZ() - v_0->getZ());

    // Calculo do produto vetorial de v1 e v2
    vn->setX((v1.getY() * v2.getZ()) - (v1.getZ() * v2.getY()));
    vn->setY((v1.getZ() * v2.getX()) - (v1.getX() * v2.getZ()));
    vn->setZ((v1.getX() * v2.getY()) - (v1.getY() * v2.getX()));

    // normalizacao de n
    len = sqrt(pow(vn->getX(), 2.0) + pow(vn->getY(), 2.0) + pow(vn->getZ(), 2.0));

    vn->setX(vn->getX() / len);
    vn->setY(vn->getY() / len);
    vn->setZ(vn->getZ() / len);
}

void PLYReader::calculateNormalFaces(PLYFile* plyFile)
{
    // Obtém a lista de faces do modelo
    vector<Primitive*>* faceList = plyFile->getFaceList();

    Triangle *tmpTriangle;
    Quad *tmpQuad;

    // Para cada face do modelo
    for(unsigned int i = 0; i < faceList->size(); i++)
    {
        // Verifica se a face é um triângulo ou um quadrado
        if(faceList->at(i)->getVertexCount() == 3)
        {
            // Faz o cast do objeto para um triângulo
            tmpTriangle = (Triangle*)(faceList->at(i));

            // Obtém os vértices da face
            Vertex3D *v0 = tmpTriangle->getV0();
            Vertex3D *v1 = tmpTriangle->getV1();
            Vertex3D *v2 = tmpTriangle->getV2();

            // Calcula o vetor normal para a superfície
            Vertex3D *vetorNormal = new Vertex3D();
            calculateNormal(v0, v1, v2, vetorNormal);

            // Adiciona o vetor normal da superfície
            plyFile->addNormal(vetorNormal);
        }
        else
        {
            // Faz o cast do objeto para um quadrado
            tmpQuad = (Quad*)(faceList->at(i));

            // Obtém os vértices da face
            Vertex3D *v0 = tmpQuad->getV0();
            Vertex3D *v1 = tmpQuad->getV1();
            Vertex3D *v2 = tmpQuad->getV2();
            //Vertex3D *v3 = tmpQuad->getV3();

            // Calcula o vetor normal para a superfície
            Vertex3D *vetorNormal = new Vertex3D();
            calculateNormal(v0, v1, v2, vetorNormal);

            // Adiciona o vetor normal da superfície
            plyFile->addNormal(vetorNormal);
        }
    }
}

void PLYReader::getMinMaxAxis(vector<Vertex3D*> *vertexList, double *minX, double *maxX, double *minY, double *maxY, double *minZ, double *maxZ)
{
    // Define os valores iniciais de mínimo/máximo para cada eixo
    *minX = vertexList->at(0)->getX();
    *maxX = vertexList->at(0)->getX();

    *minY = vertexList->at(0)->getY();
    *maxY = vertexList->at(0)->getY();

    *minZ = vertexList->at(0)->getZ();
    *maxZ = vertexList->at(0)->getZ();

    // Para todos os outros vértices
    for(unsigned int i = 1; i < vertexList->size(); i++)
    {
        // Verifica se é menor que o mínimo ou se é maior que o máximo no eixo-X
        if(vertexList->at(i)->getX() < *minX)
        {
            // Altera o valor de mínimo no eixo-X
            *minX = vertexList->at(i)->getX();
        }
        else if(vertexList->at(i)->getX() > *maxX)
        {
            // Altera o valor de máximo no eixo-X
            *maxX = vertexList->at(i)->getX();
        }

        // Verifica se é menor que o mínimo ou se é maior que o máximo no eixo-Y
        if(vertexList->at(i)->getY() < *minY)
        {
            // Altera o valor de mínimo no eixo-Y
            *minY = vertexList->at(i)->getY();
        }
        else if(vertexList->at(i)->getY() > *maxY)
        {
            // Altera o valor de máximo no eixo-Y
            *maxY = vertexList->at(i)->getY();
        }

        // Verifica se é menor que o mínimo ou se é maior que o máximo no eixo-Z
        if(vertexList->at(i)->getZ() < *minZ)
        {
            // Altera o valor de mínimo no eixo-Z
            *minZ = vertexList->at(i)->getZ();
        }
        else if(vertexList->at(i)->getZ() > *maxZ)
        {
            // Altera o valor de máximo no eixo-Z
            *maxZ = vertexList->at(i)->getZ();
        }
    }
}

void PLYReader::rescalingObject(PLYFile* plyFile)
{
    // Obtém a lista de vértices do modelo 3D
    vector<Vertex3D*>* vertexList = plyFile->getVertexList();

    // Verifica se a lista não é vazia
    if(vertexList->size() > 0)
    {
        // Obtém os valores de mínimo e máximo de cada eixo do modelo
        double minX, maxX, minY, maxY, minZ, maxZ;
        getMinMaxAxis(vertexList, &minX, &maxX, &minY, &maxY, &minZ, &maxZ);

        // Obtém os intervalos de cada eixo
        double intervalX = (maxX - minX);
        double intervalY = (maxY - minY);
        double intervalZ = (maxZ - minZ);

        // Define o valor de escala do objeto como o maior intervalo
        double scaleObj = intervalX;

        if(scaleObj < intervalY)
        {
            scaleObj = intervalY;
        }
        else if(scaleObj < intervalZ)
        {
            scaleObj = intervalZ;
        }

        double currX, currY, currZ;
        double newX, newY, newZ;

        // Escala o modelo para o intervalo [-1, 1]
        for(unsigned int i = 0; i < vertexList->size(); i++)
        {
            currX = vertexList->at(i)->getX();
            currY = vertexList->at(i)->getY();
            currZ = vertexList->at(i)->getZ();

            newX = (2 * ((currX - minX) / scaleObj)) - 1;
            newY = (2 * ((currY - minY) / scaleObj)) - 1;
            newZ = (2 * ((currZ - minZ) / scaleObj)) - 1;

            vertexList->at(i)->setX(newX);
            vertexList->at(i)->setY(newY);
            vertexList->at(i)->setZ(newZ);
        }

        // Obtém os novos valores de máximo e mínimo do modelo 3D
        getMinMaxAxis(vertexList, &minX, &maxX, &minY, &maxY, &minZ, &maxZ);

        // Obtém as coordenadas do centro do modelo 3D
        double centerX = 1.0 - ((maxX - minX) / 2.0);
        double centerY = 1.0 - ((maxY - minY) / 2.0);
        double centerZ = 1.0 - ((maxZ - minZ) / 2.0);

        // Centraliza o objeto na origem (0, 0, 0)
        for(unsigned int i = 0; i < vertexList->size(); i++)
        {
            currX = vertexList->at(i)->getX();
            currY = vertexList->at(i)->getY();
            currZ = vertexList->at(i)->getZ();

            vertexList->at(i)->setX(currX + centerX);
            vertexList->at(i)->setY(currY + centerY);
            vertexList->at(i)->setZ(currZ + centerZ);
        }
    }
}

PLYFile* PLYReader::read_ply_file(string ply_filepath)
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
    PLYFile *plyFile = new PLYFile();

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
        plyFile->setFileFormat(PLYFileVersion(ASCII_Type, fileVersion));
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
            plyFile->addComment(tmpLineValue);
        }
        else if(tmpLineValue == "element") // Verifica se a linha é de elemento
        {
            // Faz a leitura do elemento e da quantidade de elementos no arquivo PLY
            string elementName;
            int elementCount;
            strStream >> elementName >> elementCount;

            // Adiciona o elemento na lista de elementos do arquivo PLY
            plyFile->addElement(PLYFileElement(elementName, elementCount));
        }
        else if(tmpLineValue == "end_header") // Verifica se a linha é de fim de comentário
        {
            // Termina a leitura do cabeçalho do arquivo PLY
            break;
        }
    }

    // Obtém a lista de elementos do arquivo PLY
    list<PLYFileElement> elementList = plyFile->getElementList();

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
                plyFile->addVertex3D(new Vertex3D(x, y, z));
            }
        }
        else if((*it).elementName == "face") // Verifica se o elemento é o elemento de faces do modelo 3D
        {
            // Obtém a lista de vértices do modelo 3D
            vector<Vertex3D*>* vertexList = plyFile->getVertexList();
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
                    plyFile->addFace(new Triangle(v0, v1, v2));
                }
                else if(v_Count == 4) // Verifica se a quantidade de vértices é a de um quadrado
                {
                    // Obtém os vértices a partir dos índices
                    Vertex3D *v0 = vertexList->at(v_Id_arr[0]);
                    Vertex3D *v1 = vertexList->at(v_Id_arr[1]);
                    Vertex3D *v2 = vertexList->at(v_Id_arr[2]);
                    Vertex3D *v3 = vertexList->at(v_Id_arr[3]);

                    // Adiciona uma face quadrada
                    plyFile->addFace(new Quad(v0, v1, v2, v3));
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

    // Reescala e centraliza o modelo 3D
    rescalingObject(plyFile);
    // Calcula as normais das faces do modelo 3D
    calculateNormalFaces(plyFile);

    // Retorna o arquivo PLY lido
    return plyFile;
}
