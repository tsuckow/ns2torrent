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

void doNothing()
{

}

extern "C" __declspec(dllexport) int luaopen_NS2TORRENT(lua_State* L){
		
	//LuaModule::Initialize(L);

	using namespace luabind;

	open(L);
	
	module(L,"NS2TORRENT")[
		/*def("GetRootDirectory", &LuaModule::GetRootDirectory),
		def("Exists", &LuaModule::FileExists),
		def("FileSize", &LuaModule::GetFileSize),
		def("FindFiles", &LuaModule::FindFiles),
		def("FindDirectorys", &LuaModule::FindDirectorys),
		def("DateModified",  &LuaModule::GetDateModified),
		def("GetGameString",  &LuaModule::GetGameString),
		def("GetDirRootList",  &LuaModule::GetDirRootList),
		*/
		//NSRootDir::RegisterClass()

		def("DoNothing", &doNothing)
	];
	
	//push our module onto the stack tobe our return value
	lua_getglobal(L, "NS2TORRENT");

	return 1;
}
