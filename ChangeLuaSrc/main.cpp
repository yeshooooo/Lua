#include "lua.hpp"


lua_State* L;
int main()
{
	// 在c/c++中使用的是L系列的接口，底层仍然是lua_newstate,因为参数是固定的，所以没必要每次都写
	L = luaL_newstate(); 
	luaL_openlibs(L);
	luaL_dostring(L, "print 'Hello Lua!'");

	//在llex.c 词法解析中增加中文支持，这里略过
	//luaL_dostring(L, "local 变量 = 1； \n print(变量)");
	return 0;
}