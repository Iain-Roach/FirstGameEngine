#pragma once

// Windows header files:
#include <Windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "EngineCore.h"


// additional functions and macros for error-handling and retrieving modules base address
template<class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
}
}
#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif // DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

namespace Ferrus {

	class FERRUS_API EngineApp
	{
	public:
		EngineApp();
		virtual ~EngineApp();
		void Run();

		// Register the window class and call methods for instantiating
		HRESULT Initialize();

		// Process and dispatch messages || May move this to dedicated error handling section
		void RunMessageLoop();
	private:
		// Initialize device-independent resources.
		HRESULT CreateDeviceIndependentResources();

		// Initialize device-dependent resources.
		HRESULT CreateDeviceResources();


		// Release device-dependent resource.
		void DiscardDeviceResources();

		// Draw Content.
		HRESULT OnRender();

		// Resize the render target.
		void OnResize(UINT width,
			 UINT height);

		// The windows procedure.
		static LRESULT CALLBACK WndProc(
			HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);


		HWND m_hwnd;
		ID2D1Factory* m_pDirect2dFactory;
		ID2D1HwndRenderTarget* m_pRenderTarget;
		ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
		ID2D1SolidColorBrush* m_pCornflowerBlueBrush;

	};


	// Create App here
	EngineApp* CreateApplication();

}



