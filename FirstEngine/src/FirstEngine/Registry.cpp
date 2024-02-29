#include "Registry.h"

namespace Ferrus {
	Registry::Registry()
	{
	}
	size_t Registry::CreateEntity()
	{
		size_t newID = nextEntityID++;
		m_entities[newID] = Entity(newID);
		return newID;
	}
	void Registry::AddSpriteComponent(size_t entityID, SpriteComponent component) // C2064 xhash 122 errors when size_t was entity instead
	{
		if (m_entities.find(entityID) != m_entities.end())
		{
			m_sprites[entityID] = component;
		}
		else
		{
			// entityID not found 
		}
	}
	Entity& Registry::GetEntityByID(size_t entityID)
	{
		return m_entities.at(entityID);
	}

	size_t Registry::GetNextEntityID()
	{
		return nextEntityID;
	}
	std::unordered_map<size_t, SpriteComponent> Registry::GetSprites()
	{
		return m_sprites;
	}
}




