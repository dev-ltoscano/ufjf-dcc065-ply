#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../primitive/Vertex3D.h"

#define M_PI    3.14159265359

/*
Generic camera class by Nghia Ho
*/

class NavigatorCamera
{
	public:
		NavigatorCamera() { Init(); }
		~NavigatorCamera(){}

		void Init();
		void Refresh();
		void SetPos(float x, float y, float z);
		Vertex3D GetPos();
		void GetDirectionVector(float &x, float &y, float &z);
		void SetYaw(float angle);
		void SetPitch(float angle);

		// Navigation
		void Move(float incr, bool flyMode = true);
		void MoveLeft(float incr);
		void MoveRight(float incr);
		void Fly(float incr);
		void RotateYaw(float angle);
		void RotatePitch(float angle);

	private:
		float m_x, m_y, m_z;   // Position
		float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
		float m_yaw, m_pitch; // Various rotation angles
		float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector
};

#endif
