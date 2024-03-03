#pragma once

#include <d2d1.h>
#include <string>

struct FERRUS_API SpriteComponent {
	ID2D1Bitmap* pngBitmap;

	SpriteComponent() : pngBitmap(nullptr) {}
	SpriteComponent(ID2D1Bitmap* pngBitmap) : pngBitmap(pngBitmap) {}
	~SpriteComponent() {
		SafeRelease(&pngBitmap);
	}
	
};

struct FERRUS_API TransformComponent {
	float posX = 0;
	float posY = 0;

	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;
	
	float scaleX = 1;
	float scaleY = 1;
};