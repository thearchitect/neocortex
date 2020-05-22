#pragma once
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include <string>
#include "common.h"
#include "Graphics.h"
#include "Exception.h"


#define GRAPHICS  (GraphicsLayer::Graphics())
#define DEVICE (GraphicsLayer::Graphics()->GetDevice())
#define D_CONTEXT (GraphicsLayer::Graphics()->GetDeviceContext())

class D3DApplication
{
public:
	D3DApplication( HINSTANCE in_hInstance, const std::wstring& in_rAppName, const RECT& in_rFrameRect ) throw (Exception);
	virtual ~D3DApplication();

	virtual void Init() throw (Exception);
	virtual void OnPaint() throw (Exception);
	virtual void OnDestroy() throw (Exception);

	void Run(); 
	LRESULT MsgProc( HWND in_hWnd, UINT in_msg, WPARAM in_wParam, LPARAM in_lParam );

	static D3DApplication* GlobalInstance();

protected:
	// HWND accessor
	HWND _getHwnd() const;
	RECT _getFrameRect() const;
		
private:
	// Forbidden stuff
	D3DApplication( const D3DApplication& );
	D3DApplication& operator= (const D3DApplication&);
	
	// Application name
	std::wstring m_appName;
	// Frame rect
	RECT m_frameRect;
	// Application handle
	HINSTANCE m_hInstance;
	// Window handle
	HWND m_hwnd;

	// Window class name
	static const wchar_t* s_wndClassName;
	// Global application instance
	static D3DApplication* s_pApplication;
};

inline HWND D3DApplication::_getHwnd() const 
{
	return m_hwnd;
}

inline RECT D3DApplication::_getFrameRect() const
{
	return m_frameRect;
}

inline D3DApplication* D3DApplication::GlobalInstance()
{
	return s_pApplication;
}