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
