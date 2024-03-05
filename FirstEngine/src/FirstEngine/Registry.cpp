//#include "Registry.h"
//#include "EngineApp.h"
//
//namespace Ferrus {
//	Registry::Registry()
//	{
//	}
//	EntityID Registry::CreateEntity()
//	{
//		EntityID newID = nextEntityID++;
//		return newID;
//	}
//	void Registry::AddSpriteComponent(EntityID entityID, const SpriteComponent& component) // C2064 xhash 122 errors when size_t was entity instead
//	{
//		sprites[entityID] = component;
//	}
//
//	void Registry::AddTransformComponent(EntityID entityID, const TransformComponent& component)
//	{
//		transforms[entityID] = component;
//	}
//
//	bool Registry::HasSpriteComponent(EntityID entityID) const
//	{
//		return sprites.find(entityID) != sprites.end();
//	}
//
//	bool Registry::HasTransformComponent(EntityID entityID) const
//	{
//		return transforms.find(entityID) != transforms.end();
//	}
//	
//
//	const SpriteComponent& Registry::GetSpriteComponent(EntityID entityID) const
//	{
//		return sprites.at(entityID);
//	}
//
//	const TransformComponent& Registry::GetTransformComponent(EntityID entityID) const
//	{
//		return transforms.at(entityID);
//	}
//
//	EntityID Registry::GetNextEntityID()
//	{
//		return nextEntityID;
//	}
//	std::unordered_map<EntityID, SpriteComponent> Registry::GetSprites()
//	{
//		return sprites;
//	}
//
//	std::unordered_map<EntityID, TransformComponent> Registry::GetTransforms()
//	{
//		return transforms;
//	}
//
//	void Registry::LoadSpriteComponentBitmap(SpriteComponent& spriteComponent)
//	{
//
//
//	}
//
//}
//
//
//
//
