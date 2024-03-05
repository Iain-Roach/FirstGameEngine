#include "Graphics.h"
#include "EngineCore.h"

namespace Ferrus {
	Graphics::Graphics()
	{
		factory = NULL;
		renderTarget = NULL;
	}

	Graphics::~Graphics()
	{
		if (factory) factory->Release();
		if (renderTarget) renderTarget->Release();
	}

	bool Graphics::Init(HWND windowHandle)
	{
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory); // Single Threaded
		if (hr != S_OK) return false; // Could change from bool to HRESULT and return HRESULT

		RECT clientRect;
		GetClientRect(windowHandle, &clientRect); // Gets size of client area (doesn't include window header)

		hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(clientRect.right, clientRect.bottom)),
			&renderTarget);
		if (hr != S_OK) return false;

		return true;
	}
}



