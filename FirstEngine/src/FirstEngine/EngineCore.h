#pragma once


#ifdef FE_PLATFORM_WINDOWS
	#ifdef FE_BUILD_DLL
			#define FERRUS_API __declspec(dllexport)
	#else
			#define FERRUS_API __declspec(dllimport)
	#endif

#endif



