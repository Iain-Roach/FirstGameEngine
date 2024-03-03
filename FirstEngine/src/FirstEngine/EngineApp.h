#pragma once
#include "EngineCore.h"
#include "Registry.h"
#include <vector>
#include <wrl/client.h>
#include <memory>


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

		void CreateRect(float left, float right, float top, float bottom);
		
		void InitRegistry();

		Registry& GetRegistry();

		ID2D1Bitmap* LoadBitmap(const std::wstring& filePath);
		
		
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

		

		std::vector<D2D1_RECT_F> rectangles;
		Registry registry;

	};


	// Create App here
	EngineApp* CreateApplication();

}



