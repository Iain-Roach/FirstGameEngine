#include "CollisionDetection.h"
#include <cmath>

bool Ferrus::CollisionDetection::CheckCollision(D2D1_POINT_2F obj1, float radius1, D2D1_POINT_2F obj2, float radius2)
{
    float distance = sqrtf(powf((obj2.x - obj1.x), 2) + (powf((obj2.y - obj1.y), 2)));
    if (distance <= radius1 + radius2)
    {
        return true;
    }

    return false;
}
