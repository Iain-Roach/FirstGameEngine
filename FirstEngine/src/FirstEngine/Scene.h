#pragma once

#include <d2d1.h>
#include "../../ExternalHeaders/entt.hpp"
namespace Ferrus {
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry registry; // entity data/ids
	};
}

