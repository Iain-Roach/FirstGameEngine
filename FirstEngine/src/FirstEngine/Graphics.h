#pragma once
#include "EngineCore.h"



	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		bool Init(HWND windowHandle);

		void BeginDraw() { renderTarget->BeginDraw(); }
		void EndDraw() { renderTarget->EndDraw(); }
	private:
		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* renderTarget;


	};



