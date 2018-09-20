#include "stdafx.h"

C_GRAPHIC::C_GRAPHIC() :
	m_cRender(),
	m_cCamera()
{
}


void C_GRAPHIC::init(HWND hWnd)
{
	m_cRender.initD3D(hWnd);
	m_cRender.initGeometry();
	
}

void C_GRAPHIC::render()
{
	m_cRender.setupViewMatrix(m_cCamera.getMat());
	m_cRender.render();
}

void C_GRAPHIC::release()
{
	m_cRender.cleanup();
}

C_CAMERA * C_GRAPHIC::getCamera()
{
	return &m_cCamera;
}

