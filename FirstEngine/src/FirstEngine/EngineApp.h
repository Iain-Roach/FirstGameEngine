#pragma once
#include "EngineCore.h"

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

	};


	// Create App here
	EngineApp* CreateApplication();

}



