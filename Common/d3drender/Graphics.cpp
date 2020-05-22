#include "Graphics.h"

// Global instance
GraphicsLayer* GraphicsLayer::s_pMainLayer = 0;

void CreateGraphicsLayer(HWND in_hWnd, UINT in_bbWidth, UINT in_bbHeight)
{
	new GraphicsLayer(in_hWnd, in_bbWidth, in_bbHeight);
}

void DeleteGraphicsLayer()
{
	delete GraphicsLayer::Graphics();
}

GraphicsLayer* GraphicsLayer::Graphics()
{
	return s_pMainLayer;
}

GraphicsLayer::GraphicsLayer(HWND in_hWnd, UINT in_bbWidth, UINT in_bbHeight) throw(Exception)
{
	// 
	if (s_pMainLayer)
	{
		throw Exception("Graphics layer already initialized");
	}

	s_pMainLayer = this;

	// Fill out swap chain desc
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Double buffering
	swapChainDesc.BufferCount = 1;

	// Backbuffer attributes
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = in_bbWidth;
	swapChainDesc.BufferDesc.Height = in_bbHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// Buffer usage
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = in_hWnd;

	// No multi-sampling
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = TRUE;

	// Required feature levels
	D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_11_0};
	UINT numLevels = sizeof(featureLevels)/sizeof(D3D_FEATURE_LEVEL);

	// Attempt to create device and swap chain
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_DEBUG, featureLevels, numLevels, D3D11_SDK_VERSION,
		&swapChainDesc, &m_pSwapChain, &m_pDevice, &m_featureLevel, &m_pImmediateContext )))
	{
		throw Exception("Couldn't create device and swap chain");
	}

	// Retrieve default render target
	ID3D11Texture2D* pBackBuffer = NULL;
	if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer)))
	{
		throw Exception("Couldn't retrieve back buffer");
	}
	
	// Create default render target view
	if (FAILED(m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pDefaultRT)))
	{
		throw Exception("Couldn't create default render target view");
	}

	// Release back buffer
	pBackBuffer->Release();

	// Create depth-stencil texture
	D3D11_TEXTURE2D_DESC depthTextureDesc;
	ZeroMemory(&depthTextureDesc, sizeof(depthTextureDesc));
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTextureDesc.Height = in_bbHeight;
	depthTextureDesc.Width = in_bbWidth;
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;

	if (FAILED(m_pDevice->CreateTexture2D(&depthTextureDesc, NULL, &m_pDepthTexture)))
	{
		throw Exception("Couldn't create default depth-stencil");
	}

	// Create depth-stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
	ZeroMemory(&depthViewDesc, sizeof(depthViewDesc));
	depthViewDesc.Format = depthTextureDesc.Format;
	depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Texture2D.MipSlice = 0;

	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthTexture, &depthViewDesc, &m_pDefaultDS)))
	{
		throw Exception("Couldn't create default depth-stencil view");
	}

	// Set default render targte and depth stencil
	m_pImmediateContext->OMSetRenderTargets(1, &m_pDefaultRT, m_pDefaultDS);
	
	// Set viewport to cover the whole backbuffer
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = viewport.TopLeftY = 0.f;
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;
	viewport.Width = in_bbWidth;
	viewport.Height = in_bbHeight;

	m_pImmediateContext->RSSetViewports(1, &viewport);
}

GraphicsLayer::~GraphicsLayer()
{
}

void GraphicsLayer::Init() throw (Exception)
{
}

void GraphicsLayer::Present() throw (Exception)
{

	m_pSwapChain->Present(0,0);
}

void GraphicsLayer::Release() throw (Exception)
{
	m_pDefaultRT->Release();
	m_pDefaultDS->Release();
	m_pDepthTexture->Release();
	m_pImmediateContext->Release();
	m_pDevice->Release();
	m_pSwapChain->Release();
}

ID3D11DeviceContext* GraphicsLayer::GetDeviceContext() const
{
	return m_pImmediateContext;
}

ID3D11Device*		 GraphicsLayer::GetDevice() const
{
	return m_pDevice;
}

ID3D11RenderTargetView* GraphicsLayer::GetBackBuffer() const
{
	return m_pDefaultRT;
}

ID3D11DepthStencilView* GraphicsLayer::GetDepthBuffer() const
{
	return m_pDefaultDS;
}
