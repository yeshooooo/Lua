#include "LuaClass.h"

LuaClass::LuaClass(): m_lua(NULL)
{

}

LuaClass::~LuaClass()
{
	// 如果m_lua不为空,才close
	if (m_lua)
	{
		lua_close(m_lua);
	}
}

bool LuaClass::CreateLuaState()
{
	
	m_lua = luaL_newstate();
	if (m_lua == NULL)
	{
		printf("error Lua初始化环境失败! 程序异常...\n");
		return false;
	}
	luaL_openlibs(m_lua);
	return true;
	

}

void LuaClass::PrintStackSize(char* tag)
{
	if (tag)
	{
		std::cout << "堆栈大小----> " << tag << ": " << lua_gettop(m_lua) << std::endl;
	}
	else
	{
		std::cout << "堆栈大小----> " << lua_gettop(m_lua) << std::endl;
	}
}

void LuaClass::PrintStack(char* tag)
{
	int size_ = lua_gettop(m_lua);

	if (tag)
	{
		std::cout << "   ******" << tag << "******"  << std::endl;
	}
	printf("L:0x%x\n", m_lua);
	printf("size:%d\n",size_);
	for (int i = 1; i <= size_; i++)
	{
		
		printf("[%d](%s):%s\n", i, luaL_typename(m_lua, i), luaL_tolstring(m_lua,i,NULL));
		lua_pop(m_lua, 1); // 由于 luaL_tolstring 会将结果弹到堆栈,这里将他弹出来
	}
	printf("\n\n");
	
}

bool LuaClass::dofile(const char* f)
{
	if (f == NULL)
	{
		return false;
	}
	// luaL_dofile(L,文件名) 失败返回非0值,错误值字符串放入栈顶, 表面上看起来正确了返回0并且不改变堆栈
	if (luaL_dofile(m_lua, f) != 0)
	{
		
		const char* errostr = lua_tostring(m_lua, -1);
		//std::cout << "luaL_dofile: " << errostr << std::endl;
		throw std::logic_error(errostr);
		lua_pop(m_lua, 1);// 弹出堆栈顶部错误
		return false;
	} 
	else
	{
		std::cout << "成功打开文件: " << f << std::endl;
		return true;
	}
}

bool LuaClass::dostring(const char* s)
{
	if (s == NULL)
	{
		return false;
	}
	// 这里返回值用来处理错误,返回非0 表示错误
	if (luaL_dostring(m_lua, s) != 0)
	{
		const char* errostr = lua_tostring(m_lua, -1);
		//std::cout << "luaL_dostring失败: " << errostr << std::endl;
		throw std::logic_error(errostr);
		lua_pop(m_lua, 1);// 弹出堆栈顶部错误
		return false;


	}
	//std::cout << "成功打开文件: " << s << std::endl;
	return true;

}






