#include <iostream>
#include <vector>

#include <GL/glut.h>

#include "primitive/Point.h"

#include "drawable/Axis.h"
#include "drawable/Grid.h"

#include "object/Object.h"
#include "object/Ground.h"
#include "object/Brick.h"
#include "object/Player.h"

#include "ply/PLYReader.h"

#include "scene/Scene.h"

using namespace std;

enum EditMode { ModeTranslation = 0, ModeRotation = 1, ModeScale = 2, ModePLY = 3 };

inline EditMode& operator++(EditMode& mode, int)
{
    const int i = static_cast<int>(mode) + 1;
    mode = static_cast<EditMode>(i % 4);
    return mode;
}

string editModeEnumToString(EditMode mode)
{
    switch(mode)
    {
        case ModeTranslation:
            return "Translation";
        case ModeRotation:
            return "Rotation";
        case ModeScale:
            return "Scale";
        case ModePLY:
            return "PLY";
    }

    return "None";
}

int initWindowWidth = 1200, initWindowHeight = 600;
int currWindowWidth = initWindowWidth, currWindowHeight = initWindowHeight;
int currMiddleWindowWidth = (currWindowWidth / 2), currMiddleWindowHeight = (currWindowHeight / 2);
int initWindowPosX, initWindowPosY;

bool enableFullScreen = false;
bool enableWireFrame = false;
bool enableEditMode = true;
EditMode editMode = ModeTranslation;
double modeFactor = 1.0;
bool enableCollision = false;

bool lockForward = false;
bool lockBackward = false;
bool lockLeft = false;
bool lockRight = false;

// Posição atual no eixo-Z da câmera
double cam_height = 3.0;
bool nav_keyUp[256];

// Rotação do modelo 3D
double rotationX = 0.0, rotationZ = 0.0;
int last_MotionX, last_MotionZ;

PLYReader plyReader;

Scene mainScene;

int groupName = 0;
int currObjGroupIndex = 0;
ObjectGroup *currObjGroup;

int currObjIndex = 1;
Object *currObj;

Axis axis;
Grid grid(0.1, -1.0, 1.0, -1.0, 1.0);
PLYObject *highlighter;
Ground *ground;
Player player(0.0, 0.3, 0.0);
Brick *brick0;
Brick *brick1;

vector<string> plyNameList;
vector<Object*> plyList;
int currPLYIndex = -1;

// Callbacks
void init(void);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
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
        glutCreateWindow("CG - Virtual Ambient");

        // Define as callbacks
        init();
        glutKeyboardFunc(keyboard);
        glutKeyboardUpFunc(keyboardUp);
        glutSpecialFunc(specialKeyboard);
        glutMotionFunc(motion);
        glutMouseFunc(mouse);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);

        glutIgnoreKeyRepeat(1);

        cout << "# =========================================================== #" << endl;
        cout << "No modo de edição:" << endl;
        cout << "'s' -> Salva cenário" << endl;
        cout << "'l' -> Carrega cenário (EditMode != PLY) | Carrega PLY (EditMode = PLY)" << endl;
        cout << "'m' -> Alterna para o modo de navegação" << endl;
        cout << "'g' -> Cria um novo grupo" << endl;
        cout << "'c' -> Remove todos os objetos do grupo atual" << endl;
        cout << "'r' -> Remove o grupo atualmente selecionado" << endl;
        cout << "'p' -> Alterna entre o modo de edição de PLY ou de paredes" << endl;
        cout << "',' -> Diminui a espessura da parede" << endl;
        cout << "'.' -> Aumenta a espessura da parede" << endl;
        cout << "'-' -> Diminui a altura da parede" << endl;
        cout << "'+' -> Aumenta a altura da parede" << endl;
        cout << "'e' -> Alterna entre os modos de edição (Translation, Rotation, Scale, PLY)" << endl;
        cout << "'f' -> Alterna entre o fator 1.0 ou -1.0 para os modos Translation, Rotation e Scale" << endl;
        cout << "'x' -> Faz a operação de translação, rotação ou escala no eixo X do objeto selecionado (Depende de EditMode)" << endl;
        cout << "'y' -> Faz a operação de translação, rotação ou escala no eixo Y do objeto selecionado (Depende de EditMode)" << endl;
        cout << "'z' -> Faz a operação de translação, rotação ou escala no eixo Z do objeto selecionado (Depende de EditMode)" << endl;
        cout << "';' -> Desenha o wireframe da cena" << endl;
        cout << "'1 a 9' -> Define um material para os objetos do grupo" << endl;
        cout << "'Seta para cima/baixo' -> Altera o objeto selecionado do grupo" << endl;
        cout << "'Seta para cima/baixo' -> Altera o objeto PLY selecionado (EditMode = PLY)" << endl;
        cout << "'Seta para esquerda/direita' -> Altera o grupo selecionado" << endl;
        cout << "'Clique esquerdo' -> Cria um ponto no grid 2D (EditMode != PLY). 2 pontos criam uma parede" << endl;
        cout << "'Clique direito' -> Remove o último ponto criado (EditMode != PLY)" << endl;
        cout << "'Scroll up/down' -> Aumenta/diminui o zoom do cenário 3D" << endl;
        cout << "'Movimento do mouse' -> Rotaciona o cenário 3D" << endl;
        cout << "'F12' -> Habilita/desabilita o modo tela inteira" << endl;
        cout << "'ESC' -> Sai do programa" << endl << endl;
        cout << "No modo de navegação:" << endl;
        cout << "'Movimento do mouse' -> Rotaciona a câmera" << endl;
        cout << "'a', 'w', 's', 'd' -> Navega pelo cenário" << endl;
        cout << "'m' -> Alterna para o modo de edição" << endl;
        cout << "'/' -> Habilita/desabilita a colisão" << endl;
        cout << "'F12' -> Habilita/desabilita o modo tela inteira" << endl;
        cout << "'ESC' -> Sai do programa" << endl;
        cout << "# =========================================================== #" << endl;
        cout << ">>>>> AVISO: POR PADRÃO, A COLISÃO ESTÁ DESABILITADA! (Use '/' para ativar/desativar)" << endl << endl;

        glutMainLoop();
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
    GLfloat light_color0[] = { 0.5, 0.5, 0.5, 1.0};
    GLfloat light_color1[] = { 0.5, 0.5, 0.5, 1.0};
    GLfloat light0_position[] = {0.0, 1000.0, -1000.0, 0.0};
    GLfloat light1_position[] = {0.0, 1000.0, 1000.0, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_color1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color1);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
}

void enableLighting(bool enable)
{
    // Habilita/desabilita a iluminação
    if(enable)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
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

void init(void)
{
    // Define a cor de fundo como preto
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_SCISSOR_TEST);

    // Inicializa a iluminação
    initLight();
    // Habilita a iluminação
    enableLighting(true);
    // Habilita o back face culling
    enableBackFaceCulling(true);
    // Habilita o z-buffer
    enableZBuffer(true);

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    highlighter = plyReader.read_ply_file("models/arrow.ply");
    highlighter->setColor(RGBColor(1.0, 0.0, 0.0));
    highlighter->rescaling(0.2, 0.2, 0.2);
    highlighter->rotateXAxis(90.0);
    highlighter->rotateYAxis(90.0);
    highlighter->translate(0.0, 0.2, 0.0);

    ground = new Ground();
    ground->setMaterialType(Grass);
    ground->rescaling(10.0, 1.0, 10.0);

    plyList.push_back(new Brick());
    plyNameList.push_back("Brick");
    currPLYIndex = 0;

    mainScene.addNewObjectGroup(to_string(groupName++));
    currObjGroup = mainScene.getObjectGroup(currObjGroupIndex);
    currObj = NULL;
}

void timer(int value)
{
	if(nav_keyUp['w'] || nav_keyUp['W'])
	{
	    if(enableCollision)
        {
            if(!lockBackward)
            {
                ObjectGroup *tmpObjectGroup;

                for(int i = 0; i < mainScene.objectGroupListSize(); i++)
                {
                    tmpObjectGroup = mainScene.getObjectGroup(i);

                    vector<Collider*>* colliderList = tmpObjectGroup->getColliderList();
                    vector<BoundingBox*>* wallBoundingBoxList = tmpObjectGroup->getWallBoundingBoxList();

                    for(unsigned int j = 0; j < colliderList->size(); j++)
                    {
                        if(player.getCollider()->hit(colliderList->at(j)->getCollider()))
                        {
                            lockForward = true;
                            break;
                        }
                    }

                    for(unsigned int j = 0; j < wallBoundingBoxList->size(); j++)
                    {
                        if(player.getCollider()->hit(wallBoundingBoxList->at(j)))
                        {
                            lockForward = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                lockBackward = false;
                lockLeft = false;
                lockRight = false;
            }
        }

        if(!lockForward)
        {
            player.forward();
        }
	}
	else if(nav_keyUp['s'] || nav_keyUp['S'])
	{
	    if(enableCollision)
        {
            if(!lockForward)
            {
                ObjectGroup *tmpObjectGroup;

                for(int i = 0; i < mainScene.objectGroupListSize(); i++)
                {
                    tmpObjectGroup = mainScene.getObjectGroup(i);

                    vector<Collider*>* colliderList = tmpObjectGroup->getColliderList();
                    vector<BoundingBox*>* wallBoundingBoxList = tmpObjectGroup->getWallBoundingBoxList();

                    for(unsigned int j = 0; j < colliderList->size(); j++)
                    {
                        if(player.getCollider()->hit(colliderList->at(j)->getCollider()))
                        {
                            lockBackward = true;
                            break;
                        }
                    }

                    for(unsigned int j = 0; j < wallBoundingBoxList->size(); j++)
                    {
                        if(player.getCollider()->hit(wallBoundingBoxList->at(j)))
                        {
                            lockBackward = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                lockForward = false;
                lockLeft = false;
                lockRight = false;
            }
        }

        if(!lockBackward)
        {
            player.backward();
        }
	}
	else if(nav_keyUp['a'] || nav_keyUp['A'])
	{
	    if(enableCollision)
        {
            if(!lockRight)
            {
                ObjectGroup *tmpObjectGroup;

                for(int i = 0; i < mainScene.objectGroupListSize(); i++)
                {
                    tmpObjectGroup = mainScene.getObjectGroup(i);

                    vector<Collider*>* colliderList = tmpObjectGroup->getColliderList();
                    vector<BoundingBox*>* wallBoundingBoxList = tmpObjectGroup->getWallBoundingBoxList();

                    for(unsigned int j = 0; j < colliderList->size(); j++)
                    {
                        if(player.getCollider()->hit(colliderList->at(j)->getCollider()))
                        {
                            lockLeft = true;
                            break;
                        }
                    }

                    for(unsigned int j = 0; j < wallBoundingBoxList->size(); j++)
                    {
                        if(player.getCollider()->hit(wallBoundingBoxList->at(j)))
                        {
                            lockLeft = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                lockForward = false;
                lockBackward = false;
                lockLeft = false;
            }
        }

        if(!lockLeft)
        {
            player.left();
        }
	}
	else if(nav_keyUp['d'] || nav_keyUp['D'])
	{
	    if(enableCollision)
        {
            if(!lockLeft)
            {
                ObjectGroup *tmpObjectGroup;

                for(int i = 0; i < mainScene.objectGroupListSize(); i++)
                {
                    tmpObjectGroup = mainScene.getObjectGroup(i);

                    vector<Collider*>* colliderList = tmpObjectGroup->getColliderList();
                    vector<BoundingBox*>* wallBoundingBoxList = tmpObjectGroup->getWallBoundingBoxList();

                    for(unsigned int j = 0; j < colliderList->size(); j++)
                    {
                        if(player.getCollider()->hit(colliderList->at(j)->getCollider()))
                        {
                            lockRight = true;
                            break;
                        }
                    }

                    for(unsigned int j = 0; j < wallBoundingBoxList->size(); j++)
                    {
                        if(player.getCollider()->hit(wallBoundingBoxList->at(j)))
                        {
                            lockRight = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                lockForward = false;
                lockBackward = false;
                lockRight = false;
            }
        }

        if(!lockRight)
        {
            player.right();
        }
	}

	if(!enableEditMode)
    {
        glutTimerFunc(1, timer, 0);
    }
}

void keyboard(unsigned char key, int x, int y)
{
    nav_keyUp[key] = true;

    if(enableEditMode)
    {
        switch(tolower(key))
        {
            case 's':
            {
                try
                {
                    string filePath;
                    cout << "Informe o nome do arquivo a ser salvo: ";
                    cin >> filePath;

                    mainScene.saveScene(filePath);
                }
                catch(exception &ex)
                {
                    cout << endl << ">>>>> ERROR: " << ex.what() << endl;
                }
                break;
            }
            case 'l':
            {
                if(editMode != ModePLY)
                {
                    try
                    {
                        string filePath;
                        cout << "Informe o nome do arquivo a ser carregado: ";
                        cin >> filePath;

                        mainScene.loadScene(filePath);

                        currObjGroupIndex = 0;
                        currObjGroup = mainScene.getObjectGroup(currObjGroupIndex);

                        currObjIndex = 1;

                        if(currObjGroup->objectListSize() > 1)
                        {
                            currObj = currObjGroup->getObject(currObjIndex);
                        }
                        else
                        {
                            currObj = NULL;
                        }
                    }
                    catch(exception &ex)
                    {
                        cout << endl << ">>>>> ERROR: " << ex.what() << endl;
                    }
                }
                else
                {
                    try
                    {
                        string plyPath;
                        string plyName;

                        cout << "Informe o caminho do arquivo PLY: ";
                        cin >> plyPath;

                        cout << "Aguarde, carregando o arquivo " << plyPath << "...";
                        PLYObject *objPly = plyReader.read_ply_file(plyPath);
                        plyList.push_back(objPly);

                        cout << endl << "Informe um nome para o arquivo carregado: ";
                        cin >> plyName;
                        plyNameList.push_back(plyName);

                        cout << "Carregamento do arquivo PLY terminado!" << endl << endl;

                        currPLYIndex = (plyNameList.size() - 1);
                    }
                    catch(exception &ex)
                    {
                        cout << endl << ">>>>> ERROR: " << ex.what() << endl;
                    }
                }
                break;
            }
            case 'm':
            {
                enableEditMode = !enableEditMode;

                if(enableEditMode)
                {
                    glutPassiveMotionFunc(NULL);
                    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
                }
                else
                {
                    glutPassiveMotionFunc(motion);
                    glutSetCursor(GLUT_CURSOR_NONE);
                    glutTimerFunc(1, timer, 0);
                }
                break;
            }
            case 'g':
            {
                mainScene.addNewObjectGroup(to_string(groupName++));

                currObjGroupIndex = mainScene.objectGroupListSize() - 1;
                currObjGroup = mainScene.getObjectGroup(currObjGroupIndex);

                currObjIndex = 1;
                currObj = NULL;
                break;
            }
            case 'p':
            {
                if(editMode != ModePLY)
                {
                    editMode = ModePLY;
                }
                else
                {
                    editMode = ModeTranslation;
                }
                break;
            }
            case ',':
            {
                currObjGroup->decreaseWallWidth();
                break;
            }
            case '.':
            {
                currObjGroup->increaseWallWidth();
                break;
            }
            case '-':
            {
                currObjGroup->decreaseWallHeight();
                break;
            }
            case '+':
            {
                currObjGroup->increaseWallHeight();
                break;
            }
            case 'e':
            {
                editMode = editMode++;
                break;
            }
            case 'f':
            {
                modeFactor *= -1.0;
                break;
            }
            case 'x':
            {
                if(currObj != NULL)
                {
                    switch(editMode)
                    {
                        case ModeTranslation:
                        {
                            currObj->translate(0.01 * modeFactor, 0.0, 0.0);
                            break;
                        }
                        case ModeRotation:
                        {
                            Vertex3D center = currObj->getCenter();
                            currObj->centralize();
                            currObj->rotateXAxis(10.0 * modeFactor);
                            currObj->translate(center.getX(), center.getY(), center.getZ());
                            break;
                        }
                        case ModeScale:
                        {
                            Vertex3D center = currObj->getCenter();
                            currObj->centralize();

                            if(modeFactor > 0.0)
                            {
                                currObj->rescaling(1.1, 1.0, 1.0);
                            }
                            else
                            {
                                currObj->rescaling(0.9, 1.0, 1.0);
                            }

                            currObj->translate(center.getX(), center.getY(), center.getZ());
                            break;
                        }
                    }
                }
                break;
            }
            case 'y':
            {
                if(currObj != NULL)
                {
                    switch(editMode)
                    {
                        case ModeTranslation:
                        {
                            currObj->translate(0.0, 0.01 * modeFactor, 0.0);
                            break;
                        }
                        case ModeRotation:
                        {
                            Vertex3D center = currObj->getCenter();
                            currObj->centralize();
                            currObj->rotateYAxis(10.0 * modeFactor);
                            currObj->translate(center.getX(), center.getY(), center.getZ());
                            break;
                        }
                        case ModeScale:
                        {
                            Vertex3D center = currObj->getCenter();
                            currObj->centralize();

                            if(modeFactor > 0.0)
                            {
                                currObj->rescaling(1.0, 1.1, 1.0);
                            }
                            else
                            {
                                currObj->rescaling(1.0, 0.9, 1.0);
                            }

                            currObj->translate(center.getX(), center.getY(), center.getZ());
                            break;
                        }
                    }
                }
                break;
            }
            case 'z':
            {
                if(currObj != NULL)
                {
                    switch(editMode)
                    {
                        case ModeTranslation:
                        {
                            currObj->translate(0.0, 0.0, 0.01 * modeFactor);
                            break;
                        }
                        case ModeRotation:
                        {
                            Vertex3D center = currObj->getCenter();
                            currObj->centralize();
                            currObj->rotateZAxis(10.0 * modeFactor);
                            currObj->translate(center.getX(), center.getY(), center.getZ());
                            break;
                        }
                        case ModeScale:
                        {
                            Vertex3D center = currObj->getCenter();
                            currObj->centralize();

                            if(modeFactor > 0.0)
                            {
                                currObj->rescaling(1.0, 1.0, 1.1);
                            }
                            else
                            {
                                currObj->rescaling(1.0, 1.0, 0.9);
                            }
                            currObj->translate(center.getX(), center.getY(), center.getZ());
                            break;
                        }
                    }
                }
                break;
            }
            case 'c':
            {
                currObjGroup->clearGroup();

                currObjIndex = 1;
                currObj = NULL;
                break;
            }
            case 'r':
            {
                if(currObjGroupIndex > 0)
                {
                    mainScene.removeObjectGroup(currObjGroupIndex);

                    currObjGroupIndex--;
                    currObjGroup = mainScene.getObjectGroup(currObjGroupIndex);

                    currObjIndex = 1;

                    if(currObjGroup->objectListSize() > 1)
                    {
                        currObj = currObjGroup->getObject(currObjIndex);
                    }
                    else
                    {
                        currObj = NULL;
                    }
                }
                break;
            }
            case ';':
            {
                enableWireFrame = !enableWireFrame;

                if(enableWireFrame)
                {
                    enableLighting(false);
                    enableBackFaceCulling(false);
                    enableZBuffer(false);
                }
                else
                {
                    enableLighting(true);
                    enableBackFaceCulling(true);
                    enableZBuffer(true);
                }
                break;
            }
            case '1':
            {
                currObjGroup->setMaterialGroup(PolishedBronze);
                break;
            }
            case '2':
            {
                currObjGroup->setMaterialGroup(PolishedCopper);
                break;
            }
            case '3':
            {
                currObjGroup->setMaterialGroup(PolishedGold);
                break;
            }
            case '4':
            {
                currObjGroup->setMaterialGroup(PolishedSilver);
                break;
            }
            case '5':
            {
                currObjGroup->setMaterialGroup(Pewter);
                break;
            }
            case '6':
            {
                currObjGroup->setMaterialGroup(Emerald);
                break;
            }
            case '7':
            {
                currObjGroup->setMaterialGroup(Ruby);
                break;
            }
            case '8':
            {
                currObjGroup->setMaterialGroup(Turquoise);
                break;
            }
            case '9':
            {
                currObjGroup->setMaterialGroup(BlackRubber);
                break;
            }
            case 27:
                exit(0);
        }
    }
    else
    {
        switch(tolower(key))
        {
            case 'm':
            {
                enableEditMode = !enableEditMode;

                if(enableEditMode)
                {
                    glutPassiveMotionFunc(NULL);
                    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
                }
                else
                {
                    glutPassiveMotionFunc(motion);
                    glutSetCursor(GLUT_CURSOR_NONE);
                    glutTimerFunc(1, timer, 0);
                }
                break;
            }
            case '/':
            {
                enableCollision = !enableCollision;

                lockForward = false;
                lockBackward = false;
                lockLeft = false;
                lockRight = false;
                break;
            }
            case 27:
                exit(0);
        }
    }
}

void keyboardUp(unsigned char key, int x, int y)
{
	nav_keyUp[key] = false;
}

void specialKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT: // Seta direcional para esquerda
        {
            if(currObjGroupIndex > 0)
            {
                currObjGroupIndex--;
                currObjIndex = 1;

                currObjGroup = mainScene.getObjectGroup(currObjGroupIndex);

                if(currObjGroup->objectListSize() > 1)
                {
                    currObj = currObjGroup->getObject(currObjIndex);
                }
                else
                {
                    currObj = NULL;
                }
            }
            break;
        }
        case GLUT_KEY_RIGHT: // Seta direcional para direita
        {
            if(currObjGroupIndex < (mainScene.objectGroupListSize() - 1))
            {
                currObjGroupIndex++;
                currObjIndex = 1;

                currObjGroup = mainScene.getObjectGroup(currObjGroupIndex);

                if(currObjGroup->objectListSize() > 1)
                {
                    currObj = currObjGroup->getObject(currObjIndex);
                }
                else
                {
                    currObj = NULL;
                }
            }
            break;
        }
        case GLUT_KEY_UP:
        {
            if(editMode != ModePLY)
            {
                if(currObjIndex < (currObjGroup->objectListSize() - 1))
                {
                    currObjIndex++;
                    currObj = currObjGroup->getObject(currObjIndex);
                }
            }
            else
            {
                if(currPLYIndex < (plyList.size() - 1))
                {
                    currPLYIndex++;
                }
            }
            break;
        }
        case GLUT_KEY_DOWN:
        {
            if(editMode != ModePLY)
            {
                if(currObjIndex > 1)
                {
                    currObjIndex--;
                    currObj = currObjGroup->getObject(currObjIndex);
                }
            }
            else
            {
                if(currPLYIndex > 0)
                {
                    currPLYIndex--;
                }
            }
            break;
        }
        case GLUT_KEY_F12:
        {
            // Altera para o modo Fullscreen
            if(!enableFullScreen)
            {
                glutFullScreen();
            }
            else
            {
                glutReshapeWindow(initWindowWidth, initWindowHeight);
                glutPositionWindow(initWindowPosX, initWindowPosY);
            }

            enableFullScreen = !enableFullScreen;
            break;
        }
    }
}

void motion(int x, int y)
{
    if(enableEditMode)
    {
        if(x < currMiddleWindowWidth)
        {
            return;
        }

        rotationX += (double)(x - last_MotionX);
        rotationZ += (double)(y - last_MotionZ);

        last_MotionX = x;
        last_MotionZ = y;
    }
    else
    {
        player.rotate(x, y, currMiddleWindowWidth, currMiddleWindowHeight);
    }
}

void mouse(int button, int state, int x, int y)
{
    if(enableEditMode)
    {
        if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) // Botão esquerdo do mouse
        {
            // Limita o clique apenas para a Viewport dos pontos 2D
            if(x < currMiddleWindowWidth)
            {
                double posX, posY, posZ;

                posY = 0.0;

                if(x > (currMiddleWindowWidth / 2.0))
                {
                    posZ = (x / (float)(currMiddleWindowWidth / 2.0)) - 1;
                }
                else if(x == (currMiddleWindowWidth / 2.0))
                {
                    posZ = 0.0;
                }
                else
                {
                    posZ = -1.0 + (x / (float)(currMiddleWindowWidth / 2.0));
                }

                if(y == currMiddleWindowHeight)
                {
                    posX = 0.0;
                }
                else
                {
                    posX = 1 - (y / (float)currMiddleWindowHeight);
                }


                if(editMode != ModePLY)
                {
                    currObjGroup->addWallPoint(new Point(new Vertex3D(-1, posX, posY, posZ)));
                }
                else
                {
                    if(!plyList.empty())
                    {
                        Object *cloneObjPly = plyList.at(currPLYIndex)->clone();
                        cloneObjPly->rescaling(0.1, 0.1, 0.1);
                        cloneObjPly->centralize();
                        cloneObjPly->translate(posX, posY, posZ);
                        currObjGroup->addObject(cloneObjPly, true, true);

                        currObjIndex = (currObjGroup->objectListSize() - 1);
                        currObj = currObjGroup->getObject(currObjIndex);
                    }
                }
            }
        }
        else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
        {
            currObjGroup->removeLastWallPoint();
        }
        else if(button == 3) // Scroll up
        {
            cam_height -= 0.1;
        }
        else if(button == 4) // Scroll Down
        {
            cam_height += 0.1;
        }
    }

    glutPostRedisplay();
}

void idle()
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

        string windowTitle = string("CG - Virtual Ambient")
                            + string(" | FPS = ") + to_string(fps)
                            + string(" | Group = ") + to_string(currObjGroupIndex)
                            + string(" | Edit Mode = ") + editModeEnumToString(editMode)
                            + string(" | Mode Factor = ") + to_string(modeFactor)
                            + string(" | Wall = (") + to_string(currObjGroup->getWallWidth()) + ", " + to_string(currObjGroup->getWallHeight()) + ")";

        if((editMode == ModePLY) && !plyNameList.empty())
        {
            windowTitle += string(" | PLY Name = ") + plyNameList[currPLYIndex];
        }

        glutSetWindowTitle(windowTitle.c_str());
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    currWindowWidth = w;
    currWindowHeight = h;

    currMiddleWindowWidth = (currWindowWidth / 2);
    currMiddleWindowHeight = (currWindowHeight / 2);
}

void drawEditMode()
{
    vector<Point*>* pointList = currObjGroup->getWallPointList();

    if(currObj != NULL)
    {
        Vertex3D objCenter = currObj->getCenter();
        highlighter->centralize();
        highlighter->translate(objCenter.getX(), objCenter.getY() + 0.3, objCenter.getZ());
    }

    // Define a Viewport 2D
    glViewport(0, 0, currMiddleWindowWidth, currWindowHeight);

    // Limpa o fundo da Viewport com a cor branca
	glScissor(0, 0, currMiddleWindowWidth, currWindowHeight);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Define a projeção ortogonal
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.9, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    glPushMatrix();
        enableLighting(false);
            axis.draw();
            grid.draw();

            if(currObj != NULL)
            {
                highlighter->draw();
            }

            for(int i = (pointList->size() - 1); i >= 0; i--)
            {
                pointList->at(i)->draw();
            }
        enableLighting(true);

        ground->draw();

        vector<Drawable*> *tmpDrawableList;
        ObjectGroup *tmpObjectGroup;

        for(int i = 0; i < mainScene.objectGroupListSize(); i++)
        {
            tmpObjectGroup = mainScene.getObjectGroup(i);
            tmpDrawableList = tmpObjectGroup->getDrawableList();

            for(unsigned int j = 0; j < tmpDrawableList->size(); j++)
            {
                tmpDrawableList->at(j)->draw();
            }
        }
    glPopMatrix();

    // Define a Viewport 3D
	glViewport(currMiddleWindowWidth, 0, currMiddleWindowWidth, currWindowHeight);

	// Limpa o fundo da Viewport com a cor preta
	glScissor(currMiddleWindowWidth, 0, currMiddleWindowWidth, currWindowHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Define a projeção em perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, ((float)currMiddleWindowWidth / (float)currWindowHeight), 0.001, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define a posição da câmera
    gluLookAt(0.0, cam_height, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    glPushMatrix();
        glRotated(rotationZ, 0.0, 0.0, 1.0);
        glRotated(rotationX, 1.0, 0.0, 0.0);

        enableLighting(false);
            axis.draw();
            grid.draw();

            if(currObj != NULL)
            {
                highlighter->draw();
            }

            if(enableWireFrame)
            {
                ground->drawWireFrame();

                vector<Drawable*> *tmpDrawableList;
                ObjectGroup *tmpObjectGroup;

                for(int i = 0; i < mainScene.objectGroupListSize(); i++)
                {
                    tmpObjectGroup = mainScene.getObjectGroup(i);
                    tmpDrawableList = tmpObjectGroup->getDrawableList();

                    for(unsigned int j = 0; j < tmpDrawableList->size(); j++)
                    {
                        tmpDrawableList->at(j)->drawWireFrame();
                    }
                }
            }
        enableLighting(true);

        if(!enableWireFrame)
        {
            ground->draw();

            vector<Drawable*> *tmpDrawableList;
            ObjectGroup *tmpObjectGroup;

            for(int i = 0; i < mainScene.objectGroupListSize(); i++)
            {
                tmpObjectGroup = mainScene.getObjectGroup(i);
                tmpDrawableList = tmpObjectGroup->getDrawableList();

                for(unsigned int j = 0; j < tmpDrawableList->size(); j++)
                {
                    tmpDrawableList->at(j)->draw();
                }
            }
        }
    glPopMatrix();
}

void drawNavigatorMode()
{
    // Define a Viewport 3D
	glViewport(0, 0, currWindowWidth, currWindowHeight);

	// Limpa o fundo da Viewport com a cor preta
	glScissor(0, 0, currWindowWidth, currWindowHeight);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Define a projeção em perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, ((float)currWindowWidth / (float)currWindowHeight), 0.001, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    player.refresh();

    glPushMatrix();
        enableLighting(false);
            if(enableWireFrame)
            {
                ground->drawWireFrame();

                vector<Drawable*> *tmpDrawableList;
                ObjectGroup *tmpObjectGroup;

                for(int i = 0; i < mainScene.objectGroupListSize(); i++)
                {
                    tmpObjectGroup = mainScene.getObjectGroup(i);
                    tmpDrawableList = tmpObjectGroup->getDrawableList();

                    for(unsigned int j = 0; j < tmpDrawableList->size(); j++)
                    {
                        tmpDrawableList->at(j)->drawWireFrame();
                    }
                }
            }
        enableLighting(true);

        if(!enableWireFrame)
        {
            ground->draw();

            vector<Drawable*> *tmpDrawableList;
            ObjectGroup *tmpObjectGroup;

            for(int i = 0; i < mainScene.objectGroupListSize(); i++)
            {
                tmpObjectGroup = mainScene.getObjectGroup(i);
                tmpDrawableList = tmpObjectGroup->getDrawableList();

                for(unsigned int j = 0; j < tmpDrawableList->size(); j++)
                {
                    tmpDrawableList->at(j)->draw();
                }
            }
        }
    glPopMatrix();
}

void display(void)
{
    if(enableEditMode)
    {
        drawEditMode();
    }
    else
    {
        drawNavigatorMode();
    }

    glutSwapBuffers();
}
