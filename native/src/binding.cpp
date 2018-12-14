// myextension.cpp
// Extension lib defines
#define EXTENSION_NAME Native
#define LIB_NAME "Native"
#define MODULE_NAME "native"
// include the Defold SDK
#include <dmsdk/sdk.h>
#include <math.h>
#include "3d_render.h"


static char* decodeBuffer(dmBuffer::HBuffer *hBuffer, uint32_t *datasize){
	char* data = 0;
	dmBuffer::GetBytes(*hBuffer, (void**)&data, datasize);
	return data;
}

static int LoadLevelLua(lua_State* L){
     dmScript::LuaHBuffer* buffer = dmScript::CheckBuffer(L, 1);
     uint32_t datasize = 0;
     char *data = decodeBuffer(&buffer->m_Buffer,&datasize);
 	LoadLevel(data, datasize);
 	return 0;
}

static int UnloadLevelLua(lua_State* L){
	UnloadLevel();
	return 0;
}



// Functions exposed to Lua
static const luaL_reg Module_methods[] ={
	{"load_level", LoadLevelLua},
	{"unload_level", UnloadLevelLua},
	{0, 0},
};

static void LuaInit(lua_State* L){
	int top = lua_gettop(L);
	// Register lua names
	luaL_register(L, MODULE_NAME, Module_methods);
	lua_pop(L, 1);
	assert(top == lua_gettop(L));

}

static dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params){
	return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeMyExtension(dmExtension::Params* params){
	// Init Lua
	LuaInit(params->m_L);
	printf("Registered %s Extension\n", MODULE_NAME);
	return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params){
	return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params){
	return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeMyExtension, AppFinalizeMyExtension, InitializeMyExtension, 0, 0, FinalizeMyExtension)