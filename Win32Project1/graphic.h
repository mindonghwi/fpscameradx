#pragma once


#include"render.h"
#include"camera.h"

class C_GRAPHIC {
private:
	C_RENDER m_cRender;
	C_CAMERA m_cCamera;

public:
	C_GRAPHIC();

public:
	void init(HWND hWnd);
	void render();
	void release();
	C_CAMERA* getCamera();
};