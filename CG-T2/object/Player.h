#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <GL/glut.h>

#include "Object.h"
#include "../navigator/NavigatorCamera.h"
#include "../primitive/Quad.h"

class Player : public Object
{
    private:
        double nav_cam_speed = 0.025;
        double nav_cam_rot_speed = M_PI / 180 * 0.2;
        bool flyMode = false;
        bool inverseMouse = true;
        bool releaseMouse = false;

        NavigatorCamera nav_cam;
    public:
        Player(double x, double y, double z);

        void refresh();

        void forward();
        void backward();
        void left();
        void right();
        void rotate(int x, int y, int currMiddleWindowWidth, int currMiddleWindowHeight);
};

#endif // PLAYER_H_INCLUDED
