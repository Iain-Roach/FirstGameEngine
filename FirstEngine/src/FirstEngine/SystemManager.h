#pragma once
#include <memory>
#include <unordered_map>
#include "Registry.h"
#include "System.h"

namespace Ferrus {
	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			Assert(systems.find(typeName) == systems.end());

			auto system = std::make_shared<T>();
			systems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			Assert(systems.find(typeName) != systems.end());

			signatures.insert({ typeName, signature });
		}

		void EntityDestroyed(EntityID entity)
		{
			for (auto const& pair : systems)
			{
				auto const& system = pair.second;
				system->entities.erase(entity);
			}
		}

		void EntitySignatureChanged(EntityID entity, Signature entitySignature)
		{
			for (auto const& pair : systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = signatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->entities.insert(entity);
				}
				else
				{
					system->entities.erase(entity);
				}
			}
		}
	private:
		std::unordered_map<const char*, Signature> signatures{};
		std::unordered_map<const char*, std::shared_ptr<System>> systems{};
	};
}