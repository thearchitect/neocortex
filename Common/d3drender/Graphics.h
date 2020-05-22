#pragma once
#include <D3D11.h>
#include "Exception.h"

class GraphicsLayer
{
public:
	GraphicsLayer(HWND in_hWnd, UINT in_bbWidth, UINT in_bbHeight) throw(Exception);
	virtual ~GraphicsLayer();

	virtual void Init() throw (Exception);
	virtual void Present() throw (Exception);
	virtual void Release() throw (Exception);

	virtual ID3D11Device*		 GetDevice() const;
	virtual ID3D11DeviceContext* GetDeviceContext() const;
	virtual ID3D11RenderTargetView* GetBackBuffer() const;
	virtual ID3D11DepthStencilView* GetDepthBuffer() const;

	static GraphicsLayer* Graphics();

protected:
	// Feature level
	D3D_FEATURE_LEVEL m_featureLevel;
	// Direct3D device
	ID3D11Device* m_pDevice;
	// Swap chain 
	IDXGISwapChain* m_pSwapChain;
	// Immediate context
	ID3D11DeviceContext* m_pImmediateContext;
	// Default render target
	ID3D11RenderTargetView* m_pDefaultRT;
	// Default depth buffer
	ID3D11Texture2D* m_pDepthTexture;
	ID3D11DepthStencilView* m_pDefaultDS;

private:
	static GraphicsLayer* s_pMainLayer; 
};


extern void CreateGraphicsLayer(HWND in_hWnd, UINT in_bbWidth, UINT in_bbHeight);
extern void DeleteGraphicsLayer();