#include "FileLoader.h"
#include <stdexcept>
Ferrus::FileLoader::FileLoader(Graphics* gfx)
{
	this->gfx = gfx;
}

Ferrus::FileLoader::~FileLoader()
{
	
}

ID2D1Bitmap* Ferrus::FileLoader::LoadFile(PCWSTR filePath, SpriteComponent* target)
{
	IWICImagingFactory* pIWICFactory = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRESULT hr;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pIWICFactory
	);

	hr = pIWICFactory->CreateDecoderFromFilename(
		filePath,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (FAILED(hr))
	{
		SafeRelease(&pIWICFactory);

		throw std::runtime_error("Failed to create decoder from filename");
	}

	// Create the initial frame.
	hr = pDecoder->GetFrame(0, &pSource);

	if (FAILED(hr))
	{
		SafeRelease(&pDecoder);

		throw std::runtime_error("Failed to create initial frame");
	}

	// Convert the image format to 32bppPBGRA
			// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
	hr = pIWICFactory->CreateFormatConverter(&pConverter);

	if (FAILED(hr))
	{
		SafeRelease(&pIWICFactory);

		throw std::runtime_error("Failed to create initial frame");
	}


	hr = pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
	);

	if (FAILED(hr))
	{
		SafeRelease(&pConverter);

		throw std::runtime_error("Failed Initialize converter");
	}

	ID2D1Bitmap* temp = NULL;

	// Create a Direct2D bitmap from the WIC bitmap.
	hr = gfx->getRenderTarget()->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&target->BitMap
	);

	

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return temp;
}
