
#include "LuaHelp.h"

namespace LuaHelp {


	bool GetGlobal(lua_State* m_lua, char* name)
	{
		if (lua_getglobal(m_lua, name) <= 0)
		{
			throw std::logic_error("LuaGetGlobal erro");
			return false;
		}
		return true;
	}

	bool SetGlobal(lua_State* m_lua, char* name)
	{
		if (lua_gettop(m_lua) < 1)
		{
			return false;
		}
		lua_setglobal(m_lua, name);
		return true;
	}


	void PrintStack(lua_State* m_lua, char* tag)
	{
		int size_ = lua_gettop(m_lua);

		cout << endl;
		if (tag)
		{


			cout << "    ******" << tag << "******" << endl;
		}
		printf("L:0x%x\n", m_lua);
		printf("size:%d\n", size_);
		for (int i = 1; i <= size_; i++)
		{
			printf("[%d](%s):%s\n", i, luaL_typename(m_lua, i), luaL_tolstring(m_lua, i, NULL));
			lua_pop(m_lua, 1);
		}
		cout << endl;

	}
}