#include "Scene.h"

Ferrus::Scene::Scene()
{
	struct SpriteComponent
	{
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
	};
	struct TransformComponent
	{
		D2D_POINT_2F Pos;
		float Rot;
		D2D_POINT_2F Scale;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const D2D_POINT_2F& pos, const float& rot, const D2D_POINT_2F& scale) : Pos(pos), Rot(rot), Scale(scale) {}
	};

	entt::entity entity = registry.create();

	auto& t = registry.emplace<TransformComponent>(entity, D2D1::Point2F(0.0f, 0.0f), 0.0f, D2D1::Point2F(1.0f, 1.0f));

	t = TransformComponent(D2D1::Point2F(0.0f, 0.0f), 0.0f, D2D1::Point2F(2.0f, 2.0f));

	if (registry.try_get<TransformComponent>(entity))
	{
		t = TransformComponent(D2D1::Point2F(0.0f, 0.0f), 0.0f, D2D1::Point2F(2.0f, 2.0f));
	}


	TransformComponent& ta = registry.get<TransformComponent>(entity); // returns reference to transform component
	// ta = TransformComponent(...);
	
	// iterates through every entity that contains transform component
	auto view = registry.view<TransformComponent, SpriteComponent>();
	for (auto entity : view)
	{
		//auto& tran = view.get<TransformComponent>(entity);
		//auto& sprite = view.get<SpriteComponent>(entity);

		// auto [tran, sprite] = view.get<TransformComponent, SpriteComponent>(entity);
	}

	auto group = registry.group<TransformComponent, SpriteComponent>();
	for (auto entity : group)
	{
		auto& tran = group.get<TransformComponent>(entity);
		auto& sprite = group.get<TransformComponent>(entity);
	}
}

Ferrus::Scene::~Scene()
{
}
