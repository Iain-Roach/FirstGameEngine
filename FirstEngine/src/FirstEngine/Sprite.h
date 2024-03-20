#pragma once
#include <wincodec.h>
#include "Graphics.h"


	class Sprite
	{
	public:
		Sprite(PCWSTR filePath, Graphics* gfx);
		Sprite(ID2D1Bitmap* bmp, Graphics* gfx);
		~Sprite();

		void Draw(float x, float y);

		ID2D1Bitmap* GetBitMap() { return bmp; }

	private:
		Graphics* gfx;
		ID2D1Bitmap* bmp;
	};



