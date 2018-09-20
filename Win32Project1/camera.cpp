#include "stdafx.h"

C_CAMERA::C_CAMERA() :
	m_fRidYaw(0.0f),
	m_vecPos(0.0f, 0.0f, 0.0f),
	m_fRidPitch(0.0f),
	m_vecDir(0.0f, 0.0f, 0.0f),
	m_vecHorigentalDir(0.0f,0.0f,0.0f)
{
	D3DXMatrixIdentity(&m_matRotation);
	D3DXMatrixIdentity(&m_matView);
	m_vecDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecHorigentalDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_vecPos.y = 2.0f;
	updataMatPosition();
}

const D3DXMATRIX & C_CAMERA::getMat()
{
	return m_matView;
}

void C_CAMERA::moveForward()
{
	m_vecPos += m_vecDir*1.0f;
	updataMatPosition();
}

void C_CAMERA::moveBack()
{
	m_vecPos -= m_vecDir*1.0f;
	updataMatPosition();
}

void C_CAMERA::moveLeft()
{
	m_vecPos -= m_vecHorigentalDir*1.0f;
	updataMatPosition();
}

void C_CAMERA::moveRight()
{
	m_vecPos += m_vecHorigentalDir*1.0f;
	updataMatPosition();
}

void C_CAMERA::rotationYaw(float fRid)
{
	makeRotation(m_fRidYaw, fRid);
}

void C_CAMERA::retationPitch(float fRid)
{
	makeRotation(m_fRidPitch, fRid);
}

void C_CAMERA::makeStandardRid(float & fRid)
{
	int nShare = (int)(fRid / (D3DX_PI * 2.0f));
	fRid -= (D3DX_PI * 2.0f) * (float)nShare;
}

void C_CAMERA::updataMatPosition()
{
	m_matRotation._41 = m_vecPos.x;
	m_matRotation._42 = m_vecPos.y;
	m_matRotation._43 = m_vecPos.z;

	D3DXMatrixInverse(&m_matView, nullptr, &m_matRotation);
}

void C_CAMERA::updateRotation()
{
	D3DXMatrixRotationYawPitchRoll(&m_matRotation, m_fRidYaw, m_fRidPitch, 0.0f);
	D3DXVECTOR3 vZ(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformCoord(&m_vecDir, &vZ, &m_matRotation);
	D3DXVECTOR3 vX(1.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&m_vecHorigentalDir, &vX, &m_matRotation);
	updataMatPosition();
}

void C_CAMERA::makeRotation(float & fEulerAxis, float fRid)
{
	fEulerAxis += fRid;
	makeStandardRid(fEulerAxis);
	updateRotation();
}
