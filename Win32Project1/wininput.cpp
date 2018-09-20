#include "stdafx.h"



C_WININPUT::C_WININPUT() :
	m_arKey{},
	m_arMouse{},
	m_nMousePosX(0),
	m_nMousePosY(0),
	m_nMouseOffsetX(0),
	m_nMouseOffsetY(0)
{
	for (int i = 0; i < 256; i++)
	{
		m_arKey[i] = E_STATE::E_UP;
	}
	for (int i = 0; i < (int)E_MOUSEBTN::E_MAX; i++)
	{
		m_arMouse[i] = E_STATE::E_UP;
	}
}

C_WININPUT::E_STATE C_WININPUT::getKeyState(BYTE byteApiVirtualKey)
{
	return m_arKey[byteApiVirtualKey];
}

C_WININPUT::E_STATE C_WININPUT::getMouseState(E_MOUSEBTN eMouseBtn)
{
	return m_arMouse[(int)eMouseBtn];
}

//상태만 처리
bool C_WININPUT::translateMessge(const MSG * pMSG)
{
	switch (pMSG->message)
	{

	case WM_KEYDOWN:
		m_arKey[(BYTE)pMSG->wParam] = E_STATE::E_DOWN;
		return true;
	case WM_KEYUP:
		m_arKey[(BYTE)pMSG->wParam] = E_STATE::E_UP;
		return true;
	case WM_LBUTTONDOWN:
		m_arMouse[(int)E_MOUSEBTN::E_LBTN] = E_STATE::E_DOWN;
		setMousePos(pMSG->lParam);
		return true;
	case WM_LBUTTONUP:
		m_arMouse[(int)E_MOUSEBTN::E_LBTN] = E_STATE::E_UP;
		return true;
	case WM_RBUTTONDOWN:
		m_arMouse[(int)E_MOUSEBTN::E_RBTN] = E_STATE::E_DOWN;
		setMousePos(pMSG->lParam);
		return true;
	case WM_RBUTTONUP:
		m_arMouse[(int)E_MOUSEBTN::E_RBTN] = E_STATE::E_UP;
		return true;
	case WM_MOUSEMOVE:
		setMousePos(pMSG->lParam);

		m_nMouseOffsetX = -(E_MOUSE_CUR_X - m_nMousePosX);
		m_nMouseOffsetY = -(E_MOUSE_CUR_Y - m_nMousePosY);

		if (m_nMousePosX != E_MOUSE_CUR_X || m_nMousePosY != E_MOUSE_CUR_Y) {
			POINT pt = { E_MOUSE_CUR_X,E_MOUSE_CUR_Y };
			ClientToScreen(pMSG->hwnd, &pt);
			SetCursorPos(pt.x, pt.y);
		}

		RECT rcClient{};
		POINT ptLeftTop{};
		POINT ptRightBottom{};
		GetClientRect(pMSG->hwnd, &rcClient);
		ptLeftTop.x = rcClient.left;
		ptLeftTop.y = rcClient.top;
		ptRightBottom.x = rcClient.right;
		ptRightBottom.y = rcClient.left;
		ClientToScreen(pMSG->hwnd, &ptLeftTop);
		ClientToScreen(pMSG->hwnd, &ptRightBottom);
		rcClient.left = ptLeftTop.x;
		rcClient.top= ptLeftTop.y;
		rcClient.right = ptRightBottom.x;
		rcClient.left = ptRightBottom.y;
		ClipCursor(&rcClient);
		return true;
	}
	return false;
}

int C_WININPUT::getMousePosX()
{
	return m_nMousePosX;
}

int C_WININPUT::getMousePosY()
{
	return m_nMousePosY;
}

int C_WININPUT::getMouseOffsetX()
{
	return m_nMouseOffsetX;
}

int C_WININPUT::getMouseOffsetY()
{
	return m_nMouseOffsetY;
}




void C_WININPUT::setMousePos(LPARAM lParam)
{
	m_nMousePosX = GET_X_LPARAM(lParam);
	m_nMousePosY = GET_Y_LPARAM(lParam);
}