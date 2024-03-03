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



	// Currently error watch D2D tutorial : https://www.youtube.com/watch?v=RKZvT4U71rg might restructure EngineApp entirely to implement working sprites lsdkfjs

	/*ID2D1Bitmap* bitmap = app->LoadBitmapW(L"..\\..\\Assets\\TestSprite.png");
	app->GetRegistry().CreateEntity();
	SpriteComponent testSpriteComponent = SpriteComponent(bitmap);
	app->GetRegistry().AddSpriteComponent(0, testSpriteComponent);*/


	// app->CreateRect(50.0f, 100.0f, 50.0f, 370.0f);
	return app;
}