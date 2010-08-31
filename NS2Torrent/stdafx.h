// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _USE_32BIT_TIME_T
#include "targetver.h"


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

extern "C" {
	#include "lauxlib.h"
}

#include <tchar.h>

#include <string>
#include <vector>
#include <cstdint>

#if defined(UNICODE)
	#define UnicodePathString

	typedef	std::wstring PathString;
#else
	typedef	std::string PathString;
#endif

//see PathStringCover.h for all the magic of PathStringArg
//and also http://www.rasterbar.com/products/luabind/docs.html#adding-converters-for-user-defined-types
struct PathStringArg : public PathString{};

typedef PathString::value_type PathChar;

#include <luabind/luabind.hpp>
