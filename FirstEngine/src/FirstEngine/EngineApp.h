#pragma once
#include "EngineCore.h"


namespace Ferrus {

	class FERRUS_API EngineApp
	{
	public:
		EngineApp();
		virtual ~EngineApp();
		void Run();
	private:

	};


	EngineApp* CreateApplication();

}



