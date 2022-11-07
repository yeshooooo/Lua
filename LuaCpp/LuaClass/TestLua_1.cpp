#include "TestLua_1.h"

TestLua_1::TestLua_1()
{
}

TestLua_1::~TestLua_1()
{
}

void TestLua_1::Test()
{
	if (CreateLuaState())
	{
		if (!dofile("./ex3/ex5.lua"))
		{
			return;
		}
		
		if (GetGlobal("Test1"))
		{
			LuaPush<char*>("A");
			LuaPush<char*>("B");
			char* s = (char*)"GetGlobal";
			
			PrintStack(s);

			
			if (lua_pcall(GetLuaState(), 2, -1, 0) != 0)
			{
				lua_pop(GetLuaState(), 1); // µ¯³ö´íÎóÖµ
				PrintStack("lua_pcall erro");
				return;
			}
			PrintStack("lua_pcall end");
			std::cout << LuaGet<int>(1) << "," << LuaGet<int>(2) << "," << LuaGet<char*>(3) << std::endl;
			lua_pop(GetLuaState(), 3);
			PrintStack("end");
		}
		
			
			
	}
}
