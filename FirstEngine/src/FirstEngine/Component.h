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

struct CollisionComponent {
	float Radius;
	bool IsColliding;

	CollisionComponent() = default;
	CollisionComponent(const CollisionComponent&) = default;
	CollisionComponent(float radius, bool isColliding) : Radius(radius), IsColliding(isColliding) {}

	bool checkCollision(D2D1_POINT_2F obj1, float radius1, D2D1_POINT_2F obj2, float radius2)
	{
		float distance = sqrtf(powf((obj2.x - obj1.x), 2) + (powf((obj2.y - obj1.y), 2)));
		if (distance <= radius1 + radius2)
		{
			return true;
		}
		return false;
	}
};

struct ScriptComponent {
	const char* ScriptName;
	ScriptComponent() = default;
	ScriptComponent(const ScriptComponent&) = default;
	ScriptComponent(const char* scriptName) : ScriptName(scriptName) {}
};