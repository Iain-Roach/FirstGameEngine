#pragma once
#include "Registry.h"


/// <summary>
/// https://austinmorlan.com/posts/entity_component_system/
/// </summary>
namespace Ferrus
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(EntityID entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData(EntityID entity, T component)
		{
			Assert(entityToIndexMap.find(entity) == entityToIndexMap.end());

			size_t newIndex = size;
			entityToIndexMap[entity] = newIndex;
			indexToEntityMap[newIndex] = entity;
			componentArray[newIndex] = component;
			size++;
		}

		void RemoveData(EntityID entity)
		{
			Assert(entityToIndexMap.find(entity) != entityToIndexMap.end());

			size_t indexOfRemovedEntity = entityToIndexMap[entity];
			size_t indexOfLastElement = size - 1;
			componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

			EntityID entityOfLastElement = indexToEntityMap[indexOfLastElement];
			entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(indexOfLastElement);

			size--;
		}

		T& GetData(EntityID entity)
		{
			Assert(entityToIndexMap.find(entity) != entityToIndexMap.end());

			return componentArray[entityToIndexMap[entity]];
		}

		void EntityDestroyed(EntityID entity) override
		{
			if (entityToIndexMap.find(entity) != entityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}


	private:
		std::array<T, MAX_ENTITIES> componentArray;
		std::unordered_map<EntityID, size_t> entityToIndexMap;
		std::unordered_map<size_t, size_t> indexToEntityMap;

		size_t size;

	};
}

