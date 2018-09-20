#include "stdafx.h"

C_RENDER::C_RENDER():
	m_pD3D(NULL),
	m_pd3dDevice(NULL),
	m_pVB(NULL),
	m_pVBGrid(NULL)
{
	D3DXMatrixIdentity(&m_matView);
}


HRESULT C_RENDER::initD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// Create the D3DDevice
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Turn off culling, so we see the front and back of the triangle
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Turn off D3D lighting, since we are providing our own vertex colors
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

HRESULT C_RENDER::initGeometry()
{
	// Initialize three vertices for rendering a triangle
	S_CUSTOMVERTEX arVertices[] =
	{
		{ -1.0f,-1.0f, 0.0f, 0xffff0000, },
		{ 1.0f,-1.0f, 0.0f, 0xff0000ff, },
		{ 0.0f, 1.0f, 0.0f, 0xffffffff, },
	};

	// Create the vertex buffer.
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(3 * sizeof(S_CUSTOMVERTEX),
		0, E_D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return E_FAIL;
	}

	// Fill the vertex buffer.
	VOID* pVertices;
	if (FAILED(m_pVB->Lock(0, 3 * sizeof(S_CUSTOMVERTEX), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, arVertices, 3 * sizeof(S_CUSTOMVERTEX));
	m_pVB->Unlock();



	if (FAILED(m_pd3dDevice->CreateVertexBuffer(404 * sizeof(S_CUSTOMVERTEX),
		0, E_D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVBGrid, NULL)))
	{
		return E_FAIL;
	}

	S_CUSTOMVERTEX *pGridVertex = nullptr;
	if (FAILED(m_pVBGrid->Lock(0,0, (void**)&pGridVertex, 0)))
		return E_FAIL;

	float fOffSet(0.0f);
	for (int i = 0; i < 101; i++)
	{
		pGridVertex[4 * i + 0].fx = -50.0f + fOffSet;
		pGridVertex[4 * i + 0].fy = 0.0f;
		pGridVertex[4 * i + 0].fz = 50.0f;
		pGridVertex[4 * i + 0].dwColor = 0xffffffff;


		pGridVertex[4 * i + 1].fx = -50.0f + fOffSet;
		pGridVertex[4 * i + 1].fy = 0.0f;
		pGridVertex[4 * i + 1].fz = -50.0f;
		pGridVertex[4 * i + 1].dwColor = 0xffffffff;

		pGridVertex[4 * i + 2].fx = 50.0f;
		pGridVertex[4 * i + 2].fy = 0.0f;
		pGridVertex[4 * i + 2].fz = -50.0f +fOffSet;
		pGridVertex[4 * i + 2].dwColor = 0xffffffff;


		pGridVertex[4 * i + 3].fx = -50.0f;
		pGridVertex[4 * i + 3].fy = 0.0f;
		pGridVertex[4 * i + 3].fz = -50.0f +fOffSet;
		pGridVertex[4 * i + 3].dwColor = 0xffffffff;

		fOffSet += 1.0f;
	}


	m_pVBGrid->Unlock();


	return S_OK;
}

VOID C_RENDER::cleanup()
{
	if (m_pVB != NULL)
		m_pVB->Release();

	if (m_pVBGrid != NULL)
		m_pVBGrid->Release();

	if (m_pd3dDevice != NULL)
		m_pd3dDevice->Release();

	if (m_pD3D != NULL)
		m_pD3D->Release();
}

VOID C_RENDER::setupMatrices()
{
	D3DXMATRIXA16 matWorld;

	D3DXMatrixIdentity(&matWorld);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);


	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

VOID C_RENDER::render()
{
	// Clear the backbuffer to a black color
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		// Setup the world, view, and projection matrices
		setupMatrices();

		// Render the vertex buffer contents
		m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(S_CUSTOMVERTEX));
		m_pd3dDevice->SetFVF(E_D3DFVF_CUSTOMVERTEX);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);

		m_pd3dDevice->SetStreamSource(0, m_pVBGrid, 0, sizeof(S_CUSTOMVERTEX));
		m_pd3dDevice->SetFVF(E_D3DFVF_CUSTOMVERTEX);
		m_pd3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, 2*101);

		// End the scene
		m_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void C_RENDER::setupViewMatrix(const D3DXMATRIX & matView)
{
	m_matView = matView;
}
