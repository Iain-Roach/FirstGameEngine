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

		void ClearScreen(float r, float g, float b);
		void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);

	private:
		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* renderTarget;
		ID2D1SolidColorBrush* brush;

	};



