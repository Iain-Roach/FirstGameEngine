#pragma once
#include <wincodec.h>
#include "Graphics.h"


	class Sprite
	{
	public:
		Sprite(PCWSTR filePath, Graphics* gfx);
		~Sprite();

		void Draw();


	private:
		Graphics* gfx;
		ID2D1Bitmap* bmp;
	};



