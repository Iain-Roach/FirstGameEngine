#pragma once
#include <memory>
#include "ComponentManager.h"
#include "SystemManager.h"

namespace Ferrus
{
	class Coordinator
	{
	public:
		void Init()
		{
			componentManager = std::make_unique<ComponentManager>();
			registry = std::make_unique<Registry>();
			systemManager = std::make_unique<SystemManager>();
		}

		EntityID CreateEntity()
		{
			return registry->CreateEntity();
		}

		void DestroyEntity(EntityID entity)
		{
			registry->DestroyEntity(entity);
			componentManager->EntityDestroyed(entity);
			systemManager->EntityDestroyed(entity);
		}

		template<typename T>
		void RegisterComponent()
		{
			componentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{
			componentManager->AddComponent(entity, component);

			auto signature = registry->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), true);
			registry->SetSignature(entity, signature);

			systemManager->EntitySignatureChanged(entity, signature);

		}

		template<typename T>
		void RemoveComponent(EntityID entity)
		{
			componentManager->RemoveComponent<T>(entity);

			auto signature = registry->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), false);
			registry->SetSignature(entity, signature);

			systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{
			return componentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return componentManager->GetComponentType<T>();
		}

		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return systemManager->RegisterSystem();
		}

		template<typename T>
		void SetSystemSignature(Signature signature)
		{
			systemManager->SetSignature<T>(signature);
		}
	private:
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<Registry> registry;
		std::unique_ptr<SystemManager> systemManager;
	};
}
