// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
//#include "NS_IOModule.h"
//#include "SavedVariables.h"
#include <luabind/tag_function.hpp>
//#include "PathStringConverter.h"

#include "NS2Torrent.h"


BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call, LPVOID lpReserved){
	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) int luaopen_NS2Torrent(lua_State* L){

	using namespace luabind;

	open(L);
	
	module(L,"NS2Torrent")[
		//def("myFunc", &luaopen)
		NS2Torrent::RegisterClass()
	];
	
	//push our module onto the stack tobe our return value
	lua_getglobal(L, "NS2Torrent");

	return 1;
}
