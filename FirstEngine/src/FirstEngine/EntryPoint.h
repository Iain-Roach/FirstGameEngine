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

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{
	return 0;
}
#endif