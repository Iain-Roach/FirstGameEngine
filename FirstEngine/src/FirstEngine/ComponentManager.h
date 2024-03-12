#pragma once
#include "ComponentArray.h"
namespace Ferrus
{
	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent()
		{

		}

		template<typename T>
		ComponentType GetComponentType()
		{

		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{

		}

		template<typename T>
		void RemoveComponent(EntityID entity)
		{

		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{

		}

		void EntityDestroyed(EntityID entity)
		{

		}

	private:
		std::unordered_map<const char*, ComponentType> componentTypes{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};

		ComponentType nextComponent{};

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			Assert(componentType.find(typeName) != componentTypes.end());

			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
		}
	
	};
}
