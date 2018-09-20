#pragma once

#include <Windows.h>
#include "graphic.h"
#include "wininput.h"
#include "stdafx.h"

class C_MYWIN {
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	C_GRAPHIC m_cGraphic;
	C_WININPUT m_cWinInput;
private:
	C_MYWIN();
	~C_MYWIN();
	
	static C_MYWIN* m_pInstance;

	float m_fStartPosX;
	int m_nStartPosY;
	bool m_bGraphic;


public:
	C_MYWIN(const C_MYWIN &) = delete;
	void init(HINSTANCE hInstance);
	void UpdateMSG();

public:
	static void CreateInstance();
	static void ReleaseInstance();
	static C_MYWIN* GetInstance();

private:
	LRESULT CALLBACK myWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};