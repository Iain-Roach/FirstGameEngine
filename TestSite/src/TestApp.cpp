#include <Ferrus.h>
#include "../../Externals/lua/lua.hpp"
#include "../../Externals/sol/sol.hpp"
class TestSite : public Ferrus::EngineApp
{
public:
	TestSite()
	{

	}

	~TestSite()
	{

	}
private:
};






Ferrus::EngineApp* Ferrus::CreateApplication()
{
	Ferrus::EngineApp* app = new Ferrus::EngineApp;
	/*sol::state lua{};
	lua.open_libraries(sol::lib::base);
	lua.script("print('Hello World From Lua!')");
	lua.script_file("script.lua");*/
	//sol::state lua{};
	app->lua.open_libraries(sol::lib::base);
	app->lua.open_libraries(sol::lib::math);
	//app->lua.script_file("script.lua");
	const char* script = "src/script.lua";
	//app->lua.script_file(script);

	//const std::function<float(float)>& luaMoveY = app->lua["MoveY"];
	//auto testVar = luaMoveY(12);

	/*app->lua.new_usertype<Asteroid>("Asteroid",
		sol::constructors<void(), void(const Asteroid), void(TransformComponent, SpriteComponent, CollisionComponent, ScriptComponent)>(),
		"tc", &Asteroid::transformComponent,
		"sc", &Asteroid::spriteComponent,
		"cc", &Asteroid::collisiontComponent,
		"script", &Asteroid::scriptComponent);*/

	TransformComponent asteroidTransform = TransformComponent(D2D1::Point2F(100.0f, 100.0f), 0.0f, D2D1::Point2F(1.0f, 1.0f));
	SpriteComponent asteroidSprite = SpriteComponent(L"Assets\\TestSprite.png");
	CollisionComponent asteroidCollision = CollisionComponent(20.0f, false);
	ScriptComponent asteroidsScript = ScriptComponent("src/asteroid.lua");
	app->asteroidGO = AsteroidComponent(asteroidTransform, asteroidSprite, asteroidCollision, asteroidsScript);


	
	ScriptComponent testScript = ScriptComponent("src/asteroid.lua");
	ScriptComponent asteroidScript = ScriptComponent("src/asteroid.lua");


	SpriteComponent sprite = SpriteComponent(L"Assets\\TestSprite.png");
	entt::entity spriteEntityTest = app->GetRegistry().create();
	app->GetRegistry().emplace<SpriteComponent>(spriteEntityTest, sprite);
	app->GetRegistry().emplace<TransformComponent>(spriteEntityTest, D2D1::Point2F(500.0f, 200.0f), 0.0f, D2D1::Point2F(1.0f, 1.0f));

	entt::entity entt1 = app->GetRegistry().create();
	entt::entity entt2 = app->GetRegistry().create();
	entt::entity entt3 = app->GetRegistry().create();
	entt::entity entt4 = app->GetRegistry().create();
	entt::entity asteroidEntt = app->GetRegistry().create();
	app->GetRegistry().emplace<SpriteComponent>(entt1, sprite);
	app->GetRegistry().emplace<SpriteComponent>(entt2, sprite);
	app->GetRegistry().emplace<SpriteComponent>(entt3, sprite);
	app->GetRegistry().emplace<SpriteComponent>(entt4, sprite);
	app->GetRegistry().emplace<TransformComponent>(entt1, D2D1::Point2F(400.0f, 300.0f), 180.0f, D2D1::Point2F(6.0f, 6.0f));
	app->GetRegistry().emplace<TransformComponent>(entt2, D2D1::Point2F(16.0f, 584.0f), 45.0f, D2D1::Point2F(3.0f, 3.0f));
	app->GetRegistry().emplace<TransformComponent>(entt3, D2D1::Point2F(100.0f, 200.0f), 0.0f, D2D1::Point2F(2.0f, 2.0f));
	app->GetRegistry().emplace<TransformComponent>(entt4, D2D1::Point2F(700.0f, 500.0f), 315.0f, D2D1::Point2F(4.0f, 4.0f));
	app->GetRegistry().emplace<CollisionComponent>(spriteEntityTest, 10.0f, false);
	app->GetRegistry().emplace<CollisionComponent>(entt1, 45.0f, false);
	app->GetRegistry().emplace<ScriptComponent>(entt1, testScript);
	app->GetRegistry().emplace<AsteroidComponent>(entt1, app->asteroidGO);

	app->GetRegistry().emplace<TransformComponent>(asteroidEntt, asteroidTransform);
	app->GetRegistry().emplace<SpriteComponent>(asteroidEntt, asteroidSprite);
	app->GetRegistry().emplace<CollisionComponent>(asteroidEntt, asteroidCollision);
	app->GetRegistry().emplace<ScriptComponent>(asteroidEntt, asteroidsScript);
	app->GetRegistry().emplace<AsteroidComponent>(asteroidEntt, app->asteroidGO);



	// Currently error watch D2D tutorial : https://www.youtube.com/watch?v=RKZvT4U71rg might restructure EngineApp entirely to implement working sprites lsdkfjs

	/*ID2D1Bitmap* bitmap = app->LoadBitmapW(L"..\\..\\Assets\\TestSprite.png");
	app->GetRegistry().CreateEntity();
	SpriteComponent testSpriteComponent = SpriteComponent(bitmap);
	app->GetRegistry().AddSpriteComponent(0, testSpriteComponent);*/


	// app->CreateRect(50.0f, 100.0f, 50.0f, 370.0f);
	return app;
}