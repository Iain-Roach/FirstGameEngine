#pragma once
#include "EngineCore.h"
#include "Graphics.h"
#include <wincodec.h>
#include "Component.h"
namespace Ferrus {
class  FERRUS_API FileLoader
{
	public:
		FileLoader() = default;
		FileLoader(Graphics* gfx);
		~FileLoader();

		ID2D1Bitmap* LoadFile(PCWSTR filePath, SpriteComponent* target);
	private:
		Graphics* gfx;

	};
}
