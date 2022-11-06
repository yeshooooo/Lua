#include <lua.hpp>
#include <iostream>

lua_State* m_lua = NULL;

bool InitLua()
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
// 打印当前堆栈的大小
// 这里给个标签是为了看哪里打印的方便
// 并且遍历
void printStackSize(const char* tag)
{
	int sz = lua_gettop(m_lua); //获取堆栈大小
	printf("stacksize: %d <%s>\n", sz, tag);


}

//luaL_dostring
// 底层是luaL_loadstring() 和lua_pcall
void example1()
{
	printStackSize("emample1---");
	int ret = luaL_dostring(m_lua, "print('hello')");
	// 这里返回值用来处理错误,返回非0 表示错误
	//int ret = luaL_dostring(m_lua, "return 1,2,3");
	std::cout << ret << std::endl;
	if (ret != 0) // 失败返回非0值，失败的代码在栈顶中以字符串保存
	{
		const char* errostr =  lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;
	}
	printStackSize("emample1---"); //此时栈顶为返回值 1, 2, 3
}


// luaL_loadstring

void example2() {
	printStackSize("----example2");
	luaL_loadstring(m_lua, "print('Hello Lua')");
	printStackSize("----example2");
	int ret = lua_pcall(m_lua, 0, -1, 0);
	std::cout << "返回值：" << ret << std::endl;

	//处理错误
	if (ret != 0) // 失败返回非0值，失败的代码在栈顶中以字符串保存
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;
	}
	printStackSize("----lua_pcall");
}


// luaL_dofile
void example3()
{ 
	int ret = luaL_dofile(m_lua, "./ex3/ex3.lua");
	std::cout << "返回值: " << ret << std::endl;

	//处理错误
	if (ret != 0) // 失败返回非0值，失败的代码在栈顶中以字符串保存
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;
	}
	
}


// luaL_loadfile
void example4()
{
	int ret = luaL_loadfile(m_lua, "./ex3/ex3.lua");
	std::cout << "返回值: " << ret << std::endl;

	//处理错误
	if (ret != 0) // 失败返回非0值，失败的代码在栈顶中以字符串保存
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;
	}
	int pcall_ret = lua_pcall(m_lua, 0, -1, 0);
	if (pcall_ret != 0)
	{
		std::cout << "pcall error" << std::endl;
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;

	}
	printStackSize("执行完毕！");
}

// get/set global
void example5()
{
	printStackSize("1");
	lua_pushstring(m_lua, "hello"); // 向栈顶压入一个值
	printStackSize("2");
	lua_setglobal(m_lua, "xxx"); // 将栈顶的值设置为变量并且弹出栈顶的值，变量名为xxx
	printStackSize("3");
	int ret = luaL_dofile(m_lua, "./ex3/ex5.lua");
	std::cout << "返回值: " << ret << std::endl;

	//处理错误
	if (ret != 0) // 失败返回非0值，失败的代码在栈顶中以字符串保存
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;
	}


	ret =  lua_getglobal(m_lua, "data");
	std::cout << ret << std::endl;

	//错误处理
	//if (ret == LUA_TNIL || LUA_TNONE) // 在全局表不存在的时候
	if (ret <= 0) //简化
	{
		printStackSize("不存在全局变量"); // 他会把错误值压入堆栈
		lua_pop(m_lua, 1);
		return;
	}

}

// 读取基本类型
void example6()
{
	printStackSize("1");
	lua_pushstring(m_lua, "hello"); // 向栈顶压入一个值
	printStackSize("2");
	lua_setglobal(m_lua, "xxx"); // 将栈顶的值设置为变量并且弹出栈顶的值，变量名为xxx
	printStackSize("3");
	int ret = luaL_dofile(m_lua, "./ex3/ex5.lua");


	//处理错误
	if (ret != 0) // 失败返回非0值，失败的代码在栈顶中以字符串保存
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;
	}


	// 全局变量法
#if 0
	ret = lua_getglobal(m_lua, "data");
	//std::cout << ret << std::endl;

	//错误处理
	//if (ret == LUA_TNIL || LUA_TNONE) // 在全局表不存在的时候
	if (ret <= 0) //简化
	{
		printStackSize("不存在全局变量"); // 他会把错误值压入堆栈
		lua_pop(m_lua, 1);
		return;
	}
	printStackSize("------");
	//std::cout << lua_tonumber(m_lua, -1) << std::endl; // 一般用tonumber ，因为他既能取小数，也能取整数（弱类型转换）
	std::cout << lua_tostring(m_lua, -1) << std::endl; // tostring 一般不管整数还是小数都能取出来
	printStackSize("------");
#endif

	// 不用全局变量
	lua_pushstring(m_lua, "123.0");
	printStackSize("-------");
	std::cout << lua_tonumber(m_lua, -1) << std::endl;
	std::cout << lua_tointeger(m_lua, -1) << std::endl;
	printStackSize("------");


}


// 弱类型检查
void example7()
{
	printStackSize("1");
	lua_pushstring(m_lua, "hello"); // 向栈顶压入一个值
	printStackSize("2");
	lua_setglobal(m_lua, "xxx"); // 将栈顶的值设置为变量并且弹出栈顶的值，变量名为xxx
	printStackSize("3");
	int ret = luaL_dofile(m_lua, "./ex3/ex5.lua");


	//处理错误
	if (ret != 0) // 失败返回非0值，失败的代码在栈顶中以字符串保存
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// 错误处理后要把这个值给弹出
		lua_pop(m_lua, 1);// 这个宏本质上还是lua_settop()
		return;
	}


	// 全局变量法
#if 1
	ret = lua_getglobal(m_lua, "data");
	//std::cout << ret << std::endl;

	//错误处理
	//if (ret == LUA_TNIL || LUA_TNONE) // 在全局表不存在的时候
	if (ret <= 0) //简化
	{
		printStackSize("不存在全局变量"); // 他会把错误值压入堆栈
		lua_pop(m_lua, 1);
		return;
	}

	printStackSize("------");
#endif


	std::cout << lua_isnumber(m_lua, -1) << std::endl;
	std::cout << lua_isinteger(m_lua, -1) << std::endl;
	printStackSize("------");

	printf("lua_type\n");
	std::cout << lua_type(m_lua, -1) << std::endl;
	std::cout << lua_typename(m_lua, lua_type(m_lua,-1)) << std::endl;



}

int main() {
	if (InitLua() == false)
	{
		return 0;
	}

	example7();

	return 0;
}