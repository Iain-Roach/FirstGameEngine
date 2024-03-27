#pragma once
#include <d2d1.h>
namespace Ferrus {
	static class CollisionDetection
	{
	public:
		bool CheckCollision(D2D1_POINT_2F obj1, float radius1, D2D1_POINT_2F obj2, float radius2);
	private:
	};
}

