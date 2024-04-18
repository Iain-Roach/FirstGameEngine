#pragma once
//#define SOL_NO_EXCEPTIONS 1
#include "EngineCore.h"
#include "Registry.h"
#include <vector>
#include <wrl/client.h>
#include <memory>
#include "Graphics.h"
#include "Sprite.h"
#include "../../ExternalHeaders/entt.hpp"
#include "../../../Externals/lua/lua.hpp"
#include "../../../Externals/sol/sol.hpp"
#include "Component.h"
#include "FileLoader.h"
namespace Ferrus {

	class FERRUS_API EngineApp
	{
	public:
		EngineApp();
		~EngineApp();
		HRESULT Run(HINSTANCE hInstance, int nCmdShow);

		void Update();
		void OnRender();
		void MessageLoop();

		HRESULT initFileLoader(Graphics* gfx);
		FileLoader* GetFileLoader();
		entt::registry& GetRegistry() { return registry; }

		// Register the window class
		HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);
		
		
		
		sol::state lua;
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
		float t = 0.0f;

		// Test vars for bouncing ball
		float ySpeed = 0.0f;
		float yPos = 0.0f;
		
		FileLoader* fileLoader;
		Sprite* sprite;
		Graphics* graphics;
		entt::registry registry;
		
	};
	
	// Create App here
	EngineApp* CreateApplication();

}



