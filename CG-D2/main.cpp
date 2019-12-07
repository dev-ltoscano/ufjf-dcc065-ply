#include <iostream>
#include <exception>
#include <string>
#include <list>
#include <vector>

#include <GL/glut.h>

#include "Materials.h"
#include "PLYReader.h"
#include "PLYFile.h"

using namespace std;

// Tamanho inicial da janela
int initWindowWidth = 600, initWindowHeight = 600;
// Tamanho atual da janela
int currWindowWidth = initWindowWidth, currWindowHeight = initWindowHeight;
// Indica se a janela está no modo Fullscreen
bool isFullscreenWindow = false;
// Posição inicial da janela
int initWindowPosX, initWindowPosY;

// Leitor de arquivos PLY
PLYReader plyReader;
// Lista de arquivos PLY lidos
vector<PLYFile*> plyFileList;
// Índice do arquivo PLY atualmente selecionado
unsigned int currentPLYFileIndex = 0;
// Arquivo PLY atualmente selecionado
PLYFile* currentPLYFile;

// Indica se está no modo de desenho wireframe
bool drawWireFrame = false;
// Indica se o back face culling está ligado
bool backFaceCulling = true;
// Indica se o z-buffer está ligado
bool zBuffer = true;

// Rotação do modelo 3D
double rotationX = 0.0, rotationY = 0.0;
// Guarda o último movimento do mouse
int last_MotionX, last_MotionY;

// Posição atual no eixo-Z da câmera
double cam_pos_z = 3.0;

// Callbacks
void init(void);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void idle(void);
void reshape(int w, int h);
void display(void);

int main(int argc, char** argv)
{
    try
    {
        // Inicializa o GLUT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(initWindowWidth, initWindowHeight);
        initWindowPosX = ((glutGet(GLUT_SCREEN_WIDTH) - initWindowWidth) / 2);
        initWindowPosY = ((glutGet(GLUT_SCREEN_HEIGHT) - initWindowHeight) / 2);
        glutInitWindowPosition(initWindowPosX, initWindowPosY);
        glutCreateWindow("CG - PLY Viewer");

        // Define as callbacks
        init();
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKeyboard);
        glutMotionFunc(motion);
        glutMouseFunc(mouse);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);

        cout << "# =========================================================== #" << endl << endl;
        cout << "1) Botão esquerdo do mouse + movimento do mouse - Rotaciona o objeto 3D" << endl;
        cout << "2) Scroll up/Scroll down - Aumenta/diminui o zoom no objeto 3D" << endl;
        cout << "3) Setas esquerda/direita - Retrocede/avança nos arquivos PLY carregados" << endl;
        cout << "4) 1 a 9 - Faz a troca do material do objeto" << endl;
        cout << "5) 'W'/'w' - Habilita/desabilita wireframe" << endl;
        cout << "6) 'C'/'c' - Habilita/desabilita back face culling" << endl;
        cout << "7) 'Z'/'z' - Habilita/desabilita z-buffer" << endl;
        cout << "8) 'L'/'l' - Carrega um arquivo PLY" << endl;
        cout << "9) 'F12' - Habilita/desabilita modo fullscreen" << endl;
        cout << "10) 'ESC' - Encerra o programa" << endl << endl;
        cout << "# =========================================================== #" << endl << endl;

        cout << ">>>>> Aguarde, carregando arquivos PLY...";

        // Lê os arquivos PLY padrões
        plyFileList.push_back(plyReader.read_ply_file("models/budda.ply"));
        plyFileList.push_back(plyReader.read_ply_file("models/bunny.ply"));
        plyFileList.push_back(plyReader.read_ply_file("models/cow.ply"));
        plyFileList.push_back(plyReader.read_ply_file("models/dragon.ply"));
        plyFileList.push_back(plyReader.read_ply_file("models/dragon_full.ply"));
        plyFileList.push_back(plyReader.read_ply_file("models/snowman.ply"));

        // Define o arquivo PLY atual
        currentPLYFile = plyFileList[currentPLYFileIndex];

        cout << "OK!" << endl << endl;

        glutMainLoop();

        // Desaloca a memória dos arquivos PLY
        for(unsigned int i = 0; i < plyFileList.size(); i++)
        {
            delete plyFileList[i];
        }
    }
    catch(exception &ex)
    {
        cout << ">>>>> ERROR: " << ex.what() << endl;
    }

    return 0;
}

void initLight()
{
    // Inicializa o sistema de iluminação (Cor da luz, posição da luz)
    GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = { 0.0, 1000.0, 1000.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void enableLighting(bool enable)
{
    // Habilita/desabilita a iluminação
    if(enable)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
}

void enableBackFaceCulling(bool enable)
{
    // Habilita/desabilita o back face culling
    if(enable)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
}

void enableZBuffer(bool enable)
{
    // Habilita/desabilita o z-buffer
    if(enable)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

void drawAxis()
{
    // Define a espessura da linha dos eixos
    glLineWidth(2.0);

    // Desenha o eixo-X
    glBegin(GL_LINES);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(-1.0, 0.0, 0.0);
        glVertex3d(1.0, 0.0, 0.0);
    glEnd();

    // Desenha o eixo-Y
    glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    // Desenha o eixo-Z
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void drawObject()
{
    // Obtém a lista de faces do modelo 3D
    vector<Primitive*>* faceList = currentPLYFile->getFaceList();
    // Obtém a lista de normais do modelo 3D
    vector<Vertex3D*>* normalList = currentPLYFile->getNormalList();

    GLenum glPrimitive;

    // Verifica se o modo para desenhar o wireframe está habilitado
    if(drawWireFrame)
    {
        // Desliga a iluminação
        enableLighting(false);

        // Caso esteja, desenha os eixos
        drawAxis();
        // Define a primitiva do OpenGL como GL_LINE_LOOP
        glPrimitive = GL_LINE_LOOP;
        // Define a cor como rosa
        glColor3d(1.0, 0.0, 1.0);
    }
    else
    {
        // Liga a iluminação
        enableLighting(true);

        // Caso contrário, define a primitiva do OpenGL como GL_TRIANGLES
        glPrimitive = GL_TRIANGLES;
    }

    // Variáveis temporárias para desenhar as faces do modelo 3D
    Triangle *tmpTriangle;
    Quad *tmpQuad;
    Vertex3D *v0, *v1, *v2, *v3;
    Vertex3D *normalVertex;

    // Para cada face do modelo 3D
    for(unsigned int i = 0; i < faceList->size(); i++)
    {
        // Obtém o vetor normal da face
        normalVertex = normalList->at(i);

        // Verifica se a face é triangular
        if(faceList->at(i)->getVertexCount() == 3)
        {
            // Caso seja, faz o cast do objeto para um triângulo
            tmpTriangle = (Triangle*)(faceList->at(i));

            // Obtém os vértices do triângulo
            v0 = tmpTriangle->getV0();
            v1 = tmpTriangle->getV1();
            v2 = tmpTriangle->getV2();

            // Desenha o triângulo
            glBegin(glPrimitive);
                glNormal3d(normalVertex->getX(), normalVertex->getY(), normalVertex->getZ());

                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
                glVertex3d(v1->getX(), v1->getY(), v1->getZ());
                glVertex3d(v2->getX(), v2->getY(), v2->getZ());
            glEnd();
        }
        else
        {
            // Caso contrário, faz o cast do objeto para um quadrado
            tmpQuad = (Quad*)(faceList->at(i));

            // Obtém os vértices do quadrado
            v0 = tmpQuad->getV0();
            v1 = tmpQuad->getV1();
            v2 = tmpQuad->getV2();
            v3 = tmpQuad->getV3();

            // Desenha 2 triângulos a partir dos vértices do quadrado
            glBegin(glPrimitive);
                glNormal3d(normalVertex->getX(), normalVertex->getY(), normalVertex->getZ());

                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
                glVertex3d(v1->getX(), v1->getY(), v1->getZ());
                glVertex3d(v2->getX(), v2->getY(), v2->getZ());
            glEnd();

            glBegin(glPrimitive);
                glNormal3d(normalVertex->getX(), normalVertex->getY(), normalVertex->getZ());

                glVertex3d(v0->getX(), v0->getY(), v0->getZ());
                glVertex3d(v2->getX(), v2->getY(), v2->getZ());
                glVertex3d(v3->getX(), v3->getY(), v3->getZ());
            glEnd();
        }
    }
}

void init(void)
{
    // Define a cor de fundo como preto
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_SCISSOR_TEST);

    // Inicializa a iluminação
    initLight();
    // Define o material padrão dos modelos 3D
    setPolishedBronzeMaterial();
    // Habilita a iluminação
    enableLighting(true);
    // Habilita o back face culling
    enableBackFaceCulling(true);
    // Habilita o z-buffer
    enableZBuffer(true);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(tolower(key))
    {
        case 'w':
        {
            // Habilita/desabilita o desenho do wireframe
            drawWireFrame = !drawWireFrame;
            break;
        }
        case 'c':
        {
            // Habilita/desabilita o back face culling
            backFaceCulling = !backFaceCulling;
            enableBackFaceCulling(backFaceCulling);
            break;
        }
        case 'z':
        {
            // Habilita/desabilita o z-buffer
            zBuffer = !zBuffer;
            enableZBuffer(zBuffer);
            break;
        }
        case 'l':
        {
            try
            {
                string plyFilePath;
                cout << ">>>>> Caminho do arquivo PLY (Ex: models/model.ply): ";
                cin >> plyFilePath;
                cout << ">>>>> Aguarde, carregando arquivo PLY (" << plyFilePath << ")...";

                // Faz a leitura do arquivo PLY
                PLYFile *plyFile = plyReader.read_ply_file(plyFilePath);
                plyFileList.push_back(plyFile);

                // Troca o arquivo atualmente selecionado para o arquivo carregado
                currentPLYFileIndex = (plyFileList.size() - 1);
                currentPLYFile = plyFileList[currentPLYFileIndex];

                cout << "OK!" << endl;
            }
            catch(exception &ex)
            {
                cout << ex.what() << endl;
            }
            break;
        }
        case '1':
        {
            // Altera o material do modelo 3D
            setPolishedBronzeMaterial();
            break;
        }
        case '2':
        {
            // Altera o material do modelo 3D
            setPolishedCopperMaterial();
            break;
        }
        case '3':
        {
            // Altera o material do modelo 3D
            setPolishedGoldMaterial();
            break;
        }
        case '4':
        {
            // Altera o material do modelo 3D
            setPolishedBronzeMaterial();
            break;
        }
        case '5':
        {
            // Altera o material do modelo 3D
            setPewterMaterial();
            break;
        }
        case '6':
        {
            // Altera o material do modelo 3D
            setEmeraldMaterial();
            break;
        }
        case '7':
        {
            // Altera o material do modelo 3D
            setRubyMaterial();
            break;
        }
        case '8':
        {
            // Altera o material do modelo 3D
            setTurquoiseMaterial();
            break;
        }
        case '9':
        {
            // Altera o material do modelo 3D
            setBlackRubberMaterial();
            break;
        }
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT: // Seta direcional para esquerda
        {
            if(currentPLYFileIndex > 0)
            {
                // Altera o arquivo atualmente selecionado para o anterior
                currentPLYFileIndex--;
                currentPLYFile = plyFileList[currentPLYFileIndex];

                // Reseta a posição da câmera e a rotação do objeto 3D
                cam_pos_z = 3.0;
                rotationX = 0.0;
                rotationY = 0.0;
            }
            break;
        }
        case GLUT_KEY_RIGHT: // Seta direcional para direita
        {
            if(currentPLYFileIndex < (plyFileList.size() - 1))
            {
                // Altera o arquivo atualmente selecionado para o próximo
                currentPLYFileIndex++;
                currentPLYFile = plyFileList[currentPLYFileIndex];

                // Reseta a posição da câmera e a rotação do objeto 3D
                cam_pos_z = 3.0;
                rotationX = 0.0;
                rotationY = 0.0;
            }
            break;
        }
        case GLUT_KEY_F12:
        {
            // Altera para o modo Fullscreen
            if(!isFullscreenWindow)
            {
                glutFullScreen();
            }
            else
            {
                glutReshapeWindow(initWindowWidth, initWindowHeight);
                glutPositionWindow(initWindowPosX, initWindowPosY);
            }

            isFullscreenWindow = !isFullscreenWindow;
            break;
        }
    }

    glutPostRedisplay();
}

void motion(int x, int y)
{
    rotationX += (double)(x - last_MotionX);
    rotationY += (double)(y - last_MotionY);

    last_MotionX = x;
    last_MotionY = y;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    // Altera o zoom da câmera
    if(button == 3) // Scroll up
    {
        cam_pos_z -= 0.1;
    }

    if(button == 4) // Scroll Down
    {
        cam_pos_z += 0.1;
    }

    glutPostRedisplay();
}

void idle(void)
{
    // Calcula o FPS e exibe as informações na barra de título da janela
    static int frames = 0;
    static int t0 = 0;

    frames++;
    GLint t = glutGet(GLUT_ELAPSED_TIME);

    if (t - t0 >= 1000)
    {
        GLfloat seconds = (t - t0) / 1000.0;
        GLfloat fps = frames / seconds;
        t0 = t;
        frames = 0;

        string windowTitle = string("CG PLYViewer")
                       + string(" | Current = ") + to_string(currentPLYFileIndex)
                       + string(" | Vertex = ") + to_string(currentPLYFile->getVertexCount())
                       + string(" | Triangles = ") + to_string(currentPLYFile->getFaceCount())
                       + string(" | FPS = ") + to_string(fps);

        glutSetWindowTitle(windowTitle.c_str());
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    currWindowWidth = w;
    currWindowHeight = h;
}

void display(void)
{
    // Define uma Viewport
    glViewport(0, 0, currWindowWidth, currWindowHeight);
    // Limpa a Viewport
    glScissor(0, 0, currWindowWidth, currWindowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Define a projeção em perspectiva
    gluPerspective(60.0f, ((float)currWindowWidth / (float)currWindowHeight), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define a posição da câmera
    gluLookAt(0.0, 0.0, cam_pos_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Desenha o modelo 3D
    glPushMatrix();
        glRotated(rotationY, 1.0, 0.0, 0.0);
        glRotated(rotationX, 0.0, 1.0, 0.0);

        drawObject();
    glPopMatrix();

    glutSwapBuffers();
}
