#include "EngineApp.h"
#include <d2d1.h>
#include <wincodec.h>


namespace Ferrus
{
    EngineApp::EngineApp() :  hwnd(NULL)
    {
        
    }

    EngineApp::~EngineApp()
    {
        /*if (graphics) { delete graphics; graphics = nullptr; }*/

    }

    HRESULT EngineApp::Run(HINSTANCE hInstance, int nCmdShow)
    {
        if (FAILED(Initialize(hInstance, nCmdShow)))
        {
            return -1; // Initialize failed
        }

        MessageLoop();

        delete graphics;

        return 0;
    }

    void EngineApp::MessageLoop()
    {
        // Message Loop
        MSG message;
        while (GetMessage(&message, NULL, 0, 0))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        delete graphics;
    }

    HRESULT EngineApp::Initialize(HINSTANCE hInstance, int nCmdShow)
	{
        // Can move this stuff to EngineApp using method commented below ( used to be in engineapp.initialize())
        WNDCLASSEX windowClass;
        ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
        windowClass.hInstance = hInstance;
        windowClass.lpfnWndProc = WndProc;
        windowClass.lpszClassName = L"MainWindow"; // making the LPWSTR into LPCWSTR and then back fixed error???
        windowClass.style = CS_HREDRAW | CS_VREDRAW; // redraw when resized vertically / horizontally

        RegisterClassExW(&windowClass);


        RECT clientArea = { 0, 0, 800, 600 };
        AdjustWindowRectEx(&clientArea, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW); // Calculating the width and height so the client area is accurate
        HWND windowHandle = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Direct2D Engine", WS_OVERLAPPEDWINDOW, 100, 100, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top, NULL, NULL, hInstance, 0);


        if (!windowHandle) return -1;

        graphics = new Graphics();

        if (!graphics->Init(windowHandle))
        {
            delete graphics;
            return -1;
        }

        ShowWindow(windowHandle, nCmdShow);

       

        //MSG message; // MessageLoop
        //while (GetMessage(&message, NULL, 0, 0)) // NULL means get message from this threads window?
        //{
        //    DispatchMessage(&message); // allows window to dispatch the message from interactions  to the WindowProc callback
        //}

        //delete graphics;
	}

    // Will update graphics->Init to HRESULT
    HRESULT EngineApp::initGraphics(HWND hwnd)
    {
        graphics = new Graphics();
        if (!graphics) {
            return E_FAIL; // failed to allocate memory
        }

        HRESULT hr = graphics->Init(hwnd);
        if (FAILED(hr))
        {
            delete graphics;
            graphics = nullptr;
            return hr;
        }

        return S_OK;

    }
    LRESULT EngineApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_DESTROY) { PostQuitMessage(0); return 0; }

        // Window Needs to Repaint Itself
        if (message == WM_PAINT)
        {
            graphics->BeginDraw();

            graphics->ClearScreen(0.3f, 0.3f, 0.6f);

            for (int i = 0; i < 1000; i++)
            {
                graphics->DrawCircle(rand()%800, rand()%600, rand()%100, (rand()%100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
            }
            

            graphics->EndDraw();
        }



		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
}
