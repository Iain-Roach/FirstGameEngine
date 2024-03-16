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
			const char* typename = typeid(T).name();

			Assert(componentTypes.find(typename) == componentTypes.end());

			componentTypes.insert({ typeName, nextComponentType });

			componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			++nextComponentType;

		}

		template<typename T>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(T).name();

			Assert(componentTypes.find(typeName) != componentTypes.end());

			return componentTypes[typeName];
		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template<typename T>
		void RemoveComponent(EntityID entity)
		{
			GetComponentArray<T>()->RemoveData(entity);
		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{
			return GetComponentArray<T>()->GetData(entity);
		}

		void EntityDestroyed(EntityID entity)
		{
			for (auto const& pair : componentArrays)
			{
				auto const& component = pair.second;

				component->EntityDestroyed(entity);
			}
		}

	private:
		std::unordered_map<const char*, ComponentType> componentTypes{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};

		ComponentType nextComponentType{};

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			Assert(componentType.find(typeName) != componentTypes.end());

			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
		}
	
	};
}
