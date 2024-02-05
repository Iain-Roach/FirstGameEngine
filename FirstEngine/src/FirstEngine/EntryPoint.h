#pragma once


#ifdef FE_PLATFORM_WINDOWS

extern Ferrus::EngineApp* Ferrus::CreateApplication();

int main(int argc, char** argv) 
{
	printf("Hello World\n");
	auto app = Ferrus::CreateApplication();
	app->Run();
	delete app;
}
#endif