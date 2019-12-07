#include "Player.h"
#include <iostream>

Player::Player(double x, double y, double z)
{
    this->nav_cam.Init();
    this->nav_cam.SetPos(x, y, z);

    setCenter(Vertex3D(-1, x, y / 2.0, z));
    setWidth(0.1);
    setLength(0.1);
    setHeight(0.3);
}

void Player::refresh()
{
    nav_cam.Refresh();
}

void Player::forward()
{
    nav_cam.Move(nav_cam_speed, false);

    Vertex3D cam_pos = nav_cam.GetPos();
    setCenter(Vertex3D(-1, cam_pos.getX(), cam_pos.getY() / 2.0, cam_pos.getZ()));
}

void Player::backward()
{
    nav_cam.Move(-nav_cam_speed, false);

    Vertex3D cam_pos = nav_cam.GetPos();
    setCenter(Vertex3D(-1, cam_pos.getX(), cam_pos.getY() / 2.0, cam_pos.getZ()));
}

void Player::left()
{
    nav_cam.MoveLeft(-nav_cam_speed);

    Vertex3D cam_pos = nav_cam.GetPos();
    setCenter(Vertex3D(-1, cam_pos.getX(), cam_pos.getY() / 2.0, cam_pos.getZ()));
}

void Player::right()
{
    nav_cam.MoveRight(nav_cam_speed);

    Vertex3D cam_pos = nav_cam.GetPos();
    setCenter(Vertex3D(-1, cam_pos.getX(), cam_pos.getY() / 2.0, cam_pos.getZ()));
}

void Player::rotate(int x, int y, int currMiddleWindowWidth, int currMiddleWindowHeight)
{
    static bool just_warped = false;

    if(just_warped)
    {
        just_warped = false;
        return;
    }

    int dx = x - currMiddleWindowWidth;
    int dy = y - currMiddleWindowHeight;

    if(inverseMouse)
        dy = currMiddleWindowHeight - y;

    if(dx)
        nav_cam.RotateYaw(nav_cam_rot_speed * dx);

    if(dy)
        nav_cam.RotatePitch(nav_cam_rot_speed * dy);

    if(!releaseMouse)
        glutWarpPointer(currMiddleWindowWidth, currMiddleWindowHeight);

    just_warped = true;
}

//BoundingBox* Player::getBoundingBox()
//{
//    Vertex3D cam_pos = nav_cam.GetPos();
//    box->updateBox(Vertex3D(cam_pos.getX(), 0.0, cam_pos.getZ()), 0.2, 0.2, 0.3);
//    return box;
//}
