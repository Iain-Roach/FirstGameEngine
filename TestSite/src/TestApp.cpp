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
	app->CreateRect(50.0f, 100.0f, 50.0f, 150.0f);
	return app;
}