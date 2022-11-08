
#include "LuaClass.h"


LuaClass::LuaClass():m_lua(NULL)
{ 
}


LuaClass::~LuaClass()
{
	if (m_lua)
	{
		lua_close(m_lua);
	}
}


//初始化Lua环境
bool LuaClass::CreateLuaState()
{
	if (m_lua!=NULL)
	{
		return true;
	}
	m_lua = luaL_newstate();
	if (m_lua == NULL)
	{
		printf("error Lua初始化环境失败!程序异常...\n");
		return false;
	}
	luaL_openlibs(m_lua);
	return true;

}

void LuaClass::PrintStackSize(char* tag)
{
	 
	if (!tag)
	{
		cout << lua_gettop(m_lua) << endl;
	}
	else
	{
		cout << tag<<":" <<lua_gettop(m_lua) << endl;
	}

}


void LuaClass::PrintStack(char* tag)
{
	int size_ = lua_gettop(m_lua);

	cout << endl;
	if (tag)
	{ 

		
		cout <<"    ******"<<tag << "******" << endl;
	} 
	printf("L:0x%x\n", m_lua);
	printf("size:%d\n",size_);
	for (int i = 1; i <= size_; i++)
	{
		printf("[%d](%s):%s\n", i, luaL_typename(m_lua, i),luaL_tolstring(m_lua,i,NULL));
		lua_pop(m_lua, 1);
	}
	cout  << endl;

}

//#include <windows.h>
bool LuaClass::dofile(char* f)
{
	if (f==NULL)
	{
		return false;
	}
	if (luaL_dofile(m_lua, f)!=0)
	{
		char* errostr = (char*)lua_tostring(m_lua, -1); 
		throw std::logic_error(errostr);
		//::MessageBoxA(0, errostr, "dofile失败", 0);
		lua_pop(m_lua,1);
		return false;
	}

	return  true;
}



bool LuaClass::dostring(char* f)
{
	if (f == NULL)
	{
		return false;
	}
	if (luaL_dostring(m_lua, f) != 0)
	{
		char* errostr = (char*)lua_tostring(m_lua, -1); 
		throw std::logic_error(errostr);
		//::MessageBoxA(0, errostr, "dofile失败", 0);
		lua_pop(m_lua, 1);
		return false;
	}

	return  true;
}

 