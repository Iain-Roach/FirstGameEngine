//#pragma once
//
//#include <d2d1.h>
//#include <string>
//
//struct FERRUS_API SpriteComponent {
//	ID2D1Bitmap* pngBitmap;
//
//	SpriteComponent() : pngBitmap(nullptr) {}
//	SpriteComponent(ID2D1Bitmap* pngBitmap) : pngBitmap(pngBitmap) {}
//	~SpriteComponent() {
//		SafeRelease(&pngBitmap);
//	}
//	
//};
//
//struct FERRUS_API TransformComponent {
//	float posX = 0;
//	float posY = 0;
//
//	float rotX = 0;
//	float rotY = 0;
//	float rotZ = 0;
//	
//	float scaleX = 1;
//	float scaleY = 1;
//};

#pragma once

// first = x, second = y
struct TransformComponent
{
	D2D_POINT_2F Pos;
	float Rot;
	D2D_POINT_2F Scale;

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const D2D_POINT_2F& pos, const float& rot, const D2D_POINT_2F& scale) : Pos(pos), Rot(rot), Scale(scale) {}
};

struct SpriteComponent {
	ID2D1Bitmap* BitMap;
	PCWSTR FilePath;
	SpriteComponent() = default;
	SpriteComponent(const SpriteComponent&) = default;
	SpriteComponent(PCWSTR filePath) : FilePath(filePath), BitMap(NULL) {}
};