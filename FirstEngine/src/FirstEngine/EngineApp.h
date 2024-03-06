#pragma once
#include "EngineCore.h"
#include "Registry.h"
#include <vector>
#include <wrl/client.h>
#include <memory>
#include "Graphics.h"


namespace Ferrus {

	class FERRUS_API EngineApp
	{
	public:
		EngineApp();
		~EngineApp();
		HRESULT Run(HINSTANCE hInstance, int nCmdShow);
		void MessageLoop();

		// Register the window class
		HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);
		
		
	private:
		HRESULT initGraphics(HWND hwnd);

		// The windows procedure.
		static LRESULT CALLBACK WndProc(
			HWND hwnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);

		HWND hwnd;
		

	};

	Graphics* graphics;
	// Create App here
	EngineApp* CreateApplication();

}



