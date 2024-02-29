#include <Ferrus.h>

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
	app->InitRegistry(); // I should move this to apps init method so that it is automatic and I don't have to call it.
	Registry& registry = app->GetRegistry();
	registry.CreateEntity();
	SpriteComponent testComponent = { 10.0f, 100.0f, 10.0f, 100.0f };
	registry.AddSpriteComponent(0, testComponent);


	registry.CreateEntity();
	SpriteComponent anotherComponent = { 500.0f, 800.0f, 10.0f, 600.0f };
	registry.AddSpriteComponent(1, anotherComponent);

	// Things to do:
	// Registry should be initialized automatically.
	// Should I have to create a component everytime I want to add a sprite to something should I just be like ".AddSpriteComponent(all parameters go here"
	// I need a way to add and remove entities
	// I need multiple types of components
	// I need to draw the components to work with different screen size.





	// app->CreateRect(50.0f, 100.0f, 50.0f, 370.0f);
	return app;
}