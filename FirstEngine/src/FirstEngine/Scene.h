#pragma once
#include "EngineCore.h"
#include <d2d1.h>
#include "../../ExternalHeaders/entt.hpp"

// Allow client to create entities to a registry


namespace Ferrus {
	class FERRUS_API Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry registry; // entity data/ids
	};
}

