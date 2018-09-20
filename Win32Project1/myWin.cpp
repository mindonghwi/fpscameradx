#include "stdafx.h"

C_MYWIN* C_MYWIN::m_pInstance = nullptr;

C_MYWIN::C_MYWIN() :
	m_hInstance(NULL),
	m_hWnd(NULL),
	m_cGraphic(),
	m_cWinInput(),
	m_fStartPosX(0),
	m_nStartPosY(0),
	m_bGraphic(false)
{
}

C_MYWIN::~C_MYWIN()
{
}

void C_MYWIN::init(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	m_hInstance = hInstance;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"DX";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);



	m_hWnd = CreateWindowW(L"DX", nullptr, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 1024, 768, nullptr, nullptr, m_hInstance, nullptr);

	m_cGraphic.init(m_hWnd);
	m_bGraphic = true;


	if (!m_hWnd)
	{
		return;
	}

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);



}

void C_MYWIN::UpdateMSG()
{
	MSG msg = {};

	// 기본 메시지 루프입니다.
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			if (!m_cWinInput.translateMessge(&msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if (m_cWinInput.getKeyState('W') == C_WININPUT::E_STATE::E_DOWN) {
			m_cGraphic.getCamera()->moveForward();
		}
		if (m_cWinInput.getKeyState('S') == C_WININPUT::E_STATE::E_DOWN) {
			m_cGraphic.getCamera()->moveBack();
		}
		if (m_cWinInput.getKeyState('D') == C_WININPUT::E_STATE::E_DOWN) {
			m_cGraphic.getCamera()->moveRight();
		}
		if (m_cWinInput.getKeyState('A') == C_WININPUT::E_STATE::E_DOWN) {
			m_cGraphic.getCamera()->moveLeft();
		}
		float fYaw = (float)m_cWinInput.getMouseOffsetX()*0.0001f;
		float fPitch = (float)m_cWinInput.getMouseOffsetY()*0.0001f;
		m_cGraphic.getCamera()->rotationYaw(fYaw);
		m_cGraphic.getCamera()->retationPitch(fPitch);
		
		if (m_bGraphic)
			m_cGraphic.render();

	}

}

void C_MYWIN::CreateInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new C_MYWIN();
	}
}

void C_MYWIN::ReleaseInstance()
{
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

C_MYWIN* C_MYWIN::GetInstance()
{
	return m_pInstance;
}

LRESULT C_MYWIN::myWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		m_cGraphic.release();
		m_bGraphic = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT C_MYWIN::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	return m_pInstance->myWndProc(hWnd, message, wParam, lParam);
}



