#pragma once

#include<d3dx9.h>
#include <mmsystem.h>

class C_RENDER {
private:
	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	D3DXMATRIX				m_matView;

	LPDIRECT3DVERTEXBUFFER9	m_pVBGrid;

private:
	struct S_CUSTOMVERTEX
	{
		FLOAT fx, fy, fz;
		DWORD dwColor;
	};


	enum E_D3DFVF {
		E_D3DFVF_CUSTOMVERTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE,
	};

	VOID setupMatrices();

public:
	C_RENDER();
	HRESULT initD3D(HWND hWnd);
	HRESULT initGeometry();
	VOID cleanup();
	VOID render();
	void setupViewMatrix(const D3DXMATRIX &matView);
};