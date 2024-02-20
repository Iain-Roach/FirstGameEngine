#pragma once


#ifdef FE_PLATFORM_WINDOWS

extern Ferrus::EngineApp* Ferrus::CreateApplication();

int main(int argc, char** argv) 
{
	/*printf("Hello World\n");
	auto app = Ferrus::CreateApplication();
	app->Run();
	delete app;*/
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow)
{
    // Use HeapSetInformation to specify that the process should
    // terminate if the heap manager detects an error in any heap used
    // by the process.
    // The return value is ignored, because we want to continue running in the
    // unlikely event that HeapSetInformation fails.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {
            auto app = Ferrus::CreateApplication();

            if (SUCCEEDED(app->Initialize()))
            {
                app->RunMessageLoop();
            }
        }
        CoUninitialize();
    }

    return 0;
}
#endif