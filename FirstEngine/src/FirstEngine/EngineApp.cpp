#include "EngineApp.h"


namespace Ferrus
{
	EngineApp::EngineApp() : m_hwnd(NULL), m_pDirect2dFactory(NULL), m_pRenderTarget(NULL), m_pLightSlateGrayBrush(NULL), m_pCornflowerBlueBrush(NULL)
	{
	}
	EngineApp::~EngineApp()
	{
		SafeRelease(&m_pDirect2dFactory);
		SafeRelease(&m_pRenderTarget);
		SafeRelease(&m_pLightSlateGrayBrush);
		SafeRelease(&m_pCornflowerBlueBrush);
	}

	void EngineApp::RunMessageLoop()
	{
		MSG msg;
		
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

    HRESULT EngineApp::CreateDeviceIndependentResources()
    {
        return E_NOTIMPL;
    }

    HRESULT EngineApp::Initialize()
    {
        HRESULT hr;

        // Initialize device-indpendent resources, such
        // as the Direct2D factory.
        //hr = CreateDeviceIndependentResources();

        if (SUCCEEDED(hr))
        {
            // Register the window class.
            WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = EngineApp::WndProc;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = sizeof(LONG_PTR);
            wcex.hInstance = HINST_THISCOMPONENT;
            wcex.hbrBackground = NULL;
            wcex.lpszMenuName = NULL;
            wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
            wcex.lpszClassName = L"D2DDemoApp";

            RegisterClassEx(&wcex);

            // In terms of using the correct DPI, to create a window at a specific size
            // like this, the procedure is to first create the window hidden. Then we get
            // the actual DPI from the HWND (which will be assigned by whichever monitor
            // the window is created on). Then we use SetWindowPos to resize it to the
            // correct DPI-scaled size, then we use ShowWindow to show it.

           
            // why error????
            m_hwnd = CreateWindow(
                L"D2DDemoApp",
                L"Direct2D demo application",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                NULL,
                NULL,
                HINST_THISCOMPONENT,
                this);

            if (m_hwnd)
            {
                // Because the SetWindowPos function takes its size in pixels, we
                // obtain the window's DPI, and use it to scale the window size.
                float dpi = GetDpiForWindow(m_hwnd);

                SetWindowPos(
                    m_hwnd,
                    NULL,
                    NULL,
                    NULL,
                    static_cast<int>(ceil(640.f * dpi / 96.f)),
                    static_cast<int>(ceil(480.f * dpi / 96.f)),
                    SWP_NOMOVE);
                ShowWindow(m_hwnd, SW_SHOWNORMAL);
                UpdateWindow(m_hwnd);
            }
        }

        return hr;
    }

	void EngineApp::Run()
	{
		while (true);
	}
}