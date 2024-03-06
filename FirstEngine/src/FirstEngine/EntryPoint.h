#pragma once

// Need to move everything into EngineApp hopefully that will fix the issue with Grpahics not being linked properly Cope

#ifdef FE_PLATFORM_WINDOWS

extern Ferrus::EngineApp* Ferrus::CreateApplication();

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{
    if (SUCCEEDED(CoInitialize(NULL)))
    {
        auto app = Ferrus::CreateApplication();
        if (SUCCEEDED(app->Initialize(hInstance, nCmdShow)))
        {
            app->MessageLoop();
        }
        CoUninitialize();
    }

    

    return 0;
}
#endif