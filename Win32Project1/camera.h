#pragma once

#include<d3dx9.h>

class C_CAMERA
{
private:
	D3DXMATRIX m_matRotation;
	D3DXMATRIX m_matView;
	D3DXVECTOR3 m_vecDir;
	D3DXVECTOR3 m_vecPos;
	float m_fRidYaw;
	float m_fRidPitch;
	D3DXVECTOR3 m_vecHorigentalDir;

public:
	C_CAMERA();
	const D3DXMATRIX &getMat();
	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	void rotationYaw(float fRid);
	void retationPitch(float fRid);

private:
	void makeStandardRid(float &fRid);
	void updataMatPosition();
	void updateRotation();
	void makeRotation(float & fEulerAxis, float fRid);
};
