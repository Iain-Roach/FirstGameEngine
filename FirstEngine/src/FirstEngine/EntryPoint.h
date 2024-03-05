#pragma once
#include "Graphics.h"



#ifdef FE_PLATFORM_WINDOWS

extern Ferrus::EngineApp* Ferrus::CreateApplication();

Graphics* graphics;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY) { PostQuitMessage(0); return 0; }

    return DefWindowProcW(hwnd, message, wParam, lParam);
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{
    // Can move this stuff to EngineApp using method commented below ( used to be in engineapp.initialize())
    WNDCLASSEX windowClass;
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    windowClass.hInstance = hInstance;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.lpszClassName = L"MainWindow"; // making the LPWSTR into LPCWSTR and then back fixed error???
    windowClass.style = CS_HREDRAW | CS_VREDRAW; // redraw when resized vertically / horizontally

    RegisterClassExW(&windowClass);


    RECT clientArea = { 0, 0, 800, 600 };
    AdjustWindowRectEx(&clientArea, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW); // Calculating the width and height so the client area is accurate
    HWND windowHandle = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW ,L"MainWindow", L"Direct2D Engine", WS_OVERLAPPEDWINDOW, 100, 100, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top, NULL, NULL, hInstance, 0); 

    if (!windowHandle) return -1;
    
    
    graphics = new Graphics();
    if (!graphics->Init(windowHandle))
    {
        delete graphics;
        return -1;
    }
    

    ShowWindow(windowHandle, nCmdShow);

    MSG message; // MessageLoop
    while (GetMessage(&message, NULL, 0, 0)) // NULL means get message from this threads window?
    {
        DispatchMessage(&message); // allows window to dispatch the message from interactions  to the WindowProc callback
    }

    //delete graphics;

    return 0;

    //// Use HeapSetInformation to specify that the process should
    //// terminate if the heap manager detects an error in any heap used
    //// by the process.
    //// The return value is ignored, because we want to continue running in the
    //// unlikely event that HeapSetInformation fails.
    //HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    //if (SUCCEEDED(CoInitialize(NULL)))
    //{
    //    {
    //        auto app = Ferrus::CreateApplication();

    //        if (SUCCEEDED(app->Initialize()))
    //        {
    //            app->RunMessageLoop();
    //        }
    //    }
    //    CoUninitialize();
    //}

    //return 0;
}
#endif