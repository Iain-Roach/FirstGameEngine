#include "Sprite.h"
#include <stdexcept>


	Sprite::Sprite(PCWSTR filePath, Graphics* gfx)
	{
		this->gfx = gfx;
		bmp = NULL;
		HRESULT hr;

		IWICImagingFactory* pIWICFactory = NULL;
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pSource = NULL;
		IWICStream* pStream = NULL;
		IWICFormatConverter* pConverter = NULL;
		IWICBitmapScaler* pScaler = NULL;

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
		

		

			// Convert the image format to 32bppPBGRA
			// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
			hr = pIWICFactory->CreateFormatConverter(&pConverter);

		

		
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);

			

				// Create a Direct2D bitmap from the WIC bitmap.
				hr = gfx->getRenderTarget()->CreateBitmapFromWicBitmap(
					pConverter,
					NULL,
					&bmp
				);
			

			SafeRelease(&pDecoder);
			SafeRelease(&pSource);
			SafeRelease(&pStream);
			SafeRelease(&pConverter);
			SafeRelease(&pScaler);
		

		//// will move this to another file if working
		//IWICImagingFactory* wicFactory = NULL;
		//hr = CoCreateInstance(
		//	CLSID_WICImagingFactory,
		//	NULL,
		//	CLSCTX_INPROC_SERVER,
		//	IID_IWICImagingFactory,
		//	(LPVOID*)&wicFactory);

		//// create decoder
		//IWICBitmapDecoder* wicDecoder = NULL;
		//hr = wicFactory->CreateDecoderFromFilename(
		//	filePath,
		//	NULL,
		//	GENERIC_READ,
		//	WICDecodeMetadataCacheOnLoad,  // Caches on load but we removing everything anyways
		//	&wicDecoder);

		//// Read frame from image but we need whole image so we get frame 0
		//IWICBitmapFrameDecode* wicFrame = NULL;
		//hr = wicDecoder->GetFrame(0, &wicFrame);

		//// Converting WIC bitmap to D2D bitmap
		//IWICFormatConverter* wicConverter = NULL;
		//hr = wicFactory->CreateFormatConverter(&wicConverter);

		//hr = wicConverter->Initialize(
		//	wicFrame,
		//	GUID_WICPixelFormat32bppPBGRA, // Pixel Format  packed blue, green,read, alpha (why that order idk)
		//	WICBitmapDitherTypeNone,  // bot 4 involve pixel palette index
		//	NULL,
		//	0.0,
		//	WICBitmapPaletteTypeCustom
		//);


		//gfx->getRenderTarget()->CreateBitmapFromWicBitmap(
		//	wicConverter,
		//	NULL,
		//	&bmp
		//);
		//

		//// make sure to release factory and decoders when done
		//if (wicFactory) wicFactory->Release();
		//if (wicConverter) wicConverter->Release();
		//if (wicFrame) wicFrame->Release();
		//if (wicDecoder) wicDecoder->Release();
	}

	Sprite::Sprite(ID2D1Bitmap* bmp, Graphics* gfx)
	{
		this->bmp = bmp;
		this->gfx = gfx;
	}

	Sprite::~Sprite()
	{
		if (bmp) bmp->Release();
	}

	void Sprite::Draw(float x, float y)
	{
		gfx->getRenderTarget()->DrawBitmap(
			bmp,												// Bitmap
			D2D1::RectF((x - 16.0f),									// Destination rectangle (where on rendertarget to draw)
				(y - 16.0f),
				((bmp->GetSize().width) + x - 16.0f),
				(bmp->GetSize().height) + y - 16.0f),
			1.0f,												// Opacity
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	// If bitmap is streched or shrunk
			D2D1::RectF(0.0f, 0.0f,								// source rectangle
				bmp->GetSize().width, bmp->GetSize().height) 
		);
	}


