//#pragma once
//#include "EngineCore.h"
//#include <unordered_map>
//#include "Component.h"
//
//
//namespace Ferrus {
//	using EntityID = size_t;
//	class  FERRUS_API Registry
//	{
//	public:
//		Registry();
//		
//
//		EntityID CreateEntity();
//
//		void AddSpriteComponent(EntityID entityID, const SpriteComponent& component);
//		void AddTransformComponent(EntityID entityID, const TransformComponent& component);
//
//		bool HasSpriteComponent(EntityID entityID) const;
//		bool HasTransformComponent(EntityID entityID) const;
//
//		const SpriteComponent& GetSpriteComponent(EntityID entityID) const;
//		const TransformComponent& GetTransformComponent(EntityID entityID) const;
//
//		EntityID GetNextEntityID();
//
//		std::unordered_map<EntityID, SpriteComponent> GetSprites();
//		std::unordered_map<EntityID, TransformComponent> GetTransforms();
//
//		void LoadSpriteComponentBitmap(SpriteComponent& spriteComponent);
//
//
//
//	private:
//		EntityID nextEntityID = 0;
//
//		std::unordered_map<EntityID, TransformComponent> transforms;
//		std::unordered_map<EntityID, SpriteComponent> sprites;
//		
//	};
//}
//
//
//
//
//
#pragma once
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <queue>
#include <bitset>
#include <array>
#include "EngineApp.h"

/// <summary>
/// https://austinmorlan.com/posts/entity_component_system/
/// </summary>
namespace Ferrus {
	using EntityID = size_t;
	const EntityID MAX_ENTITIES = 100; // capping to small amount for now

	using ComponentType = size_t; // each component will have an id depending on what type of component it is, transform would be 0 for example
	const ComponentType MAX_COMPONENTS = 16; // the max amount of components probably will be closer to 4 (transform, sprite, input, physics)
	
	using Signature = std::bitset<MAX_COMPONENTS>; // Allows us to make sure systems use proper components using bit comparison
	
	class Registry
	{
	public:
		Registry();

		EntityID CreateEntity();
		void DestroyEntity(EntityID entity);

		void SetSignature(EntityID entity, Signature signature);
		Signature GetSignature(EntityID entity);
	private:
		std::queue<EntityID> availableEntities{};
		std::array<Signature, MAX_ENTITIES> signatures{};
		
		size_t livingEntitiesCount{};
	};
}