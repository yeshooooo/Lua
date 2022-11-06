// 因为c语言函数和c++函数的函数名在编译到系统中是不一致的，所以这里要指定一下

// 这里表示这部分函数都是以c语言定义的
extern "C"
{
#include <lua.h> // 附加包含目录里设置下就行，windows下不区分大小写
#include <lauxlib.h>
#include <lualib.h>
}


int CTest(lua_State* L) {
	printf("int CTest\n");
	size_t len;

	// lua向c++传递字符串
	const char* name =  lua_tolstring(L, 1, &len); // 第二个是，参数在栈中的位置，第三个是字符串长度
	printf("Lua name = %s\n", name);

	// lua向c++传递数字
	int age = lua_tonumber(L, 2);
	printf("Lua age = %d\n", age);

	// lua 向c++传递bool
	bool is = lua_toboolean(L, 3);
	printf("Lua Is = %d\n", is);

	return 0;
}

// 遍历lua中的数组
int CTestArr(lua_State* L) {
	printf("In CTestArr\n");
	int len = luaL_len(L, 1);
	for (int i = 1; i <= len; i++)
	{
		lua_pushnumber(L, i); // 给lua传值
		lua_gettable(L, 1); // pop index，然后push table[i]
		size_t size = 0;
		printf("%s\n", lua_tolstring(L, -1, &size)); // 因为上面把table[i]压入了栈顶
		lua_pop(L, 1); // 类似回溯？
	}
	return 0;
}

// 生成lua 状态 引用lua脚本
int main() {
	// lua 状态就是一个lua的堆栈，以下函数所有的程序都在这个堆栈中运行
	//lua_State* lua = lua_open();//这个函数在5.2中已经被遗弃，被新的函数luaL_newstate和lua_newstate替代,https://blog.csdn.net/x356982611/article/details/47405351
	lua_State* lua = luaL_newstate();

	//打开基本库
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);
	// 可以通过lua堆栈通知lua在c++中定义的函数，也可以通过定义好的函数通知
	lua_register(lua, "CTest",CTest); //第一个参数，lua堆栈，第二个：函数的名称，第三个：函数指针
	lua_register(lua, "CTestArr", CTestArr);


	//载入文件
	if (luaL_loadfile(lua, "main.lua"))
	{
		const char* error = lua_tostring(lua, -1);
		printf("lua load error:%s", error);
	}
	lua_pcall(lua, 0, 0, 0); // 2以后参数：参数个数，返回值，错误函数

	getchar();
	return 0;
}