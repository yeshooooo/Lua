#include "lua.hpp"


lua_State* L = NULL;
//初始化lua环境
void InitLua()
{
	L = luaL_newstate();
	if (L == NULL)
	{
		printf("error Lua初始化环境失败! 程序异常.....\n");
		return;
	}
	//加载全部库
	luaL_openlibs(L);

	/*
	// 手动加载特定库
	luaopen_base(L); //加载基础库,比加载
	luaopen_string(L);
	*/
}



//关键函数
// 1. lua_pushstring 放入一个字符串到Lua堆栈 ,lua_tostring获取堆栈中的字符串
// 2. lua_gettop 获取堆栈的大小
// 3. lua_settop 设置堆栈指向的位置,若指向0,则清空堆栈.


// 计算负序号
int calc(int nindex, int nsize)
{
	return nindex - nsize - 1;
}



// 打印当前堆栈的大小
// 这里给个标签是为了看哪里打印的方便
// 并且遍历
void printStack(const char* tag)
{
	int sz = lua_gettop(L); //获取堆栈大小
	printf("stacksize: %d <%s>\n", lua_gettop(L),tag);
	for (int i = 1; i <= sz; i++)
	{
		const char* str = lua_tostring(L, i);
		printf("index : %d , %d ----- %s \n", i, calc(i, sz),str);
	}

}




int main()
{
	InitLua();
	printStack("初始化完毕");
	lua_pushfstring(L,"a");
	printStack("push a");

	//lua_settop(L, 0); //清理堆栈

	lua_pushfstring(L, "b");
	printStack("push b");
	printf("----------------\n");
	lua_settop(L, 1);
	lua_pushstring(L, "c");
	printStack("push c");

	// 这里加不加lua_close都行,加上是为了代码规范,因为进程结束会自动释放资源
	lua_close(L);
	L = nullptr;
	return 0;
}