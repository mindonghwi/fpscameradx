#pragma once

#include<Windows.h>

class C_WININPUT {
public:

	enum class E_STATE {
		E_UP,
		E_DOWN,
	};
	enum class E_MOUSEBTN {
		E_LBTN,
		E_RBTN,
		E_MAX
	};
	enum {
		E_MOUSE_CUR_X = 512,
		E_MOUSE_CUR_Y = 384,
	};

private:
	E_STATE m_arKey[256];
	E_STATE m_arMouse[(int)E_MOUSEBTN::E_MAX];
	int		m_nMousePosX;
	int		m_nMousePosY;
	int		m_nMouseOffsetX;
	int		m_nMouseOffsetY;


private:
	void setMousePos(LPARAM lParam);


public:
	C_WININPUT();
	E_STATE getKeyState(BYTE byteApiVirtualKey);
	E_STATE getMouseState(E_MOUSEBTN eMouseBtn);
	bool translateMessge(const MSG* pMSG);
	int getMousePosX();
	int getMousePosY();
	int getMouseOffsetX();
	int getMouseOffsetY();
};