#include "Application.h"

// Window class name
const wchar_t* D3DApplication::s_wndClassName = L"RENDER";
// Global instance of an application
D3DApplication* D3DApplication::s_pApplication = 0;

// Message processing function
// Forwards the call to class method
static LRESULT WINAPI sMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return D3DApplication::GlobalInstance()->MsgProc(hWnd, msg, wParam, lParam);
}

// Constructor
D3DApplication::D3DApplication( HINSTANCE in_hInstance, const std::wstring& in_rAppName, const RECT& in_rFrameRect ) throw (Exception)
	: m_hInstance(in_hInstance), m_appName(in_rAppName), m_frameRect(in_rFrameRect)//add d3d stuff
{
	// Panic in the case of one instance already exist
	if (s_pApplication)
	{
		throw Exception("Application object already initialized");
	}

	// Initialize instance 
	s_pApplication = this;

	// Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, sMsgProc, 0L, 0L,
		m_hInstance, NULL, NULL, NULL, NULL,
        s_wndClassName, NULL
    };

    RegisterClassEx( &wc );

    // Create the application's window
	m_hwnd = CreateWindow( s_wndClassName, m_appName.c_str() ,
		WS_OVERLAPPEDWINDOW, m_frameRect.left, m_frameRect.top, m_frameRect.right - m_frameRect.left, m_frameRect.bottom - m_frameRect.top,
		NULL, NULL, wc.hInstance, NULL );

	// Handle errors
	if (0 == m_hwnd)
	{
		throw Exception("Couldn't create application window");
	}
}

// Destructor
D3DApplication::~D3DApplication()
{
	// Destroy global instance
	if (s_pApplication)
	{
		UnregisterClass( s_wndClassName, m_hInstance );
		s_pApplication = NULL;
	}
}

// Initialize all the stuff
void D3DApplication::Init() throw (Exception)
{
	// Get client rect in order to create back buffer  
	// of the right size
	RECT clientRect = {0,0,0,0};
	GetClientRect(m_hwnd, &clientRect);

	// Initialize graphics layer
	CreateGraphicsLayer(m_hwnd, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	GRAPHICS->Init();
}

// Message processing method
LRESULT D3DApplication::MsgProc( HWND in_hWnd, UINT in_msg, WPARAM in_wParam, LPARAM in_lParam )
{
	switch( in_msg )
	{
	case WM_DESTROY:
		OnDestroy();
		PostQuitMessage( 0 );
		return 0;

	/*case WM_PAINT:
		OnPaint();
		ValidateRect( in_hWnd, NULL );
		return 0;*/
	}

	return DefWindowProc( in_hWnd, in_msg, in_wParam, in_lParam );
}

// Application life cycle
void D3DApplication::Run()
{
	// Initialize all the stuff
	Init();

	// Show the window
	ShowWindow( m_hwnd, SW_SHOWDEFAULT );
	UpdateWindow( m_hwnd );

	// Enter the message loop
	MSG msg = {0};
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            OnPaint();
        }
	}
}

// WM_PAINT handler
void D3DApplication::OnPaint() throw (Exception)
{	
	GRAPHICS->Present();
}

// WM_DESTROY handler
void D3DApplication::OnDestroy() throw (Exception)
{
	GRAPHICS->Release();
	DeleteGraphicsLayer();
}
