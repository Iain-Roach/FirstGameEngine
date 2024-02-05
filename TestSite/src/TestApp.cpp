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
	return new TestSite();
}