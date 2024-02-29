#pragma once
#include "EngineCore.h"
#include "Entity.h"
#include <unordered_map>
#include "Component.h"


namespace Ferrus {
	class FERRUS_API Registry
	{
	public:
		Registry();

		size_t CreateEntity();

		void AddSpriteComponent(size_t entityID, SpriteComponent component);


		Entity& GetEntityByID(size_t entityID);

		size_t GetNextEntityID();

		std::unordered_map<size_t, SpriteComponent> GetSprites();


	private:
		size_t nextEntityID = 0;
		std::unordered_map<size_t, Entity> m_entities;

		std::unordered_map<size_t, SpriteComponent> m_sprites;
	};
}





