#include "EngineApp.h"
#include <d2d1.h>
#include <wincodec.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <filesystem>

namespace Ferrus
{
    EngineApp::EngineApp() :  hwnd(NULL), sprite(NULL)
    {
        
    }

    EngineApp::~EngineApp()
    {
        if (sprite) delete sprite;

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

    void EngineApp::Update()
    {
        ySpeed += 1.0f;
        yPos += ySpeed;

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        // GetClientRect not working?
        if (yPos > 600)
        {
            yPos = 600;
            ySpeed = -30.0f;

        }
    }

    void EngineApp::OnRender()
    {
        graphics->BeginDraw();

        graphics->ClearScreen(0.3f, 0.3f, 0.5f);
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        graphics->DrawCircle(375.0f, yPos, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        sprite->Draw();

        graphics->EndDraw();
    }

    void EngineApp::MessageLoop()
    {
        // Message Loop
        MSG message;
        message.message = WM_NULL;
        while (message.message != WM_QUIT)
        {
            if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                DispatchMessage(&message); // sends message to WndPrc
            }
            else
            {
                // Update
                Update();

                // Render
                OnRender();
            }
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

        std::filesystem::path currentPath = std::filesystem::current_path();
        std::stringstream stream;
        stream << "Current working directory: " << currentPath << std::endl;
        OutputDebugStringA(stream.str().c_str());

        // Will need to add error handling incase of incorrect sprite names
        try {
            sprite = new Sprite(L"Assets\\TestSprite.png", graphics);
            /*sprite = new Sprite(L"E:\\Repo\\IndependentStudyEngine\\FirstEngine\\TestSite\\Assets\\TestSprite.png", graphics);*/
        }
        catch (const std::runtime_error& e) {
            std::stringstream ss;
            ss << "Runtime error: " << e.what() << std::endl;
            OutputDebugStringA(ss.str().c_str());
        }
        

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




		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
}
