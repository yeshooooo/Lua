#include "LuaClass.h"

int a____() {
	LuaClass* mclass = new LuaClass();

	if (mclass->CreateLuaState() == false)
	{
		std::cout << "lua 初始化失败" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "lua 初始化成功" << std::endl;
	}

	/*mclass->dofile("./ex3/ex5.lua");*/
	////mclass->PrintStackSize();
	//mclass->GetGlobal("data");
	//mclass->GetGlobal("data2");
	//std::cout << mclass->LuaGet<int>(-2) << std::endl;
	//std::cout << mclass->LuaGet<char*>() << std::endl;
	//std::cout << mclass->LuaGet<std::string>() << std::endl;
	//mclass->LuaPush<int>(123);
	//std::cout << mclass->LuaGet<int>() << std::endl;
	//mclass->LuaPush<char*>((char*)"123");
	//std::cout << mclass->LuaGet<char*>() << std::endl;
	mclass->PrintStackSize();
	mclass->LuaSetGlobal<int>(110, "Test");
	std::cout << mclass->LuaGetGlobal<int>("Test") << std::endl;
	mclass->dofile("./ex3/ex5.lua");
	//std::cout << mclass->LuaGetGlobal<int>("data") << std::endl;
	//std::cout << mclass->LuaGetGlobal<char*>("data2") << std::endl;
	//std::cout << mclass->LuaGetGlobal<std::string>("data2") << std::endl;
	mclass->PrintStackSize();
	return 0;
}
#include "TestLua_1.h"
int main()
{
	//LuaClass* mclass = new LuaClass();
	//if (mclass->CreateLuaState() == false)
	//{
	//	return 0;
	//}
	//
	//mclass->LuaPush<int>(1213);
	////mclass->LuaPush<double>(1.1324);
	////mclass->LuaPush<char*>((char*)"hello");
	//mclass->PrintStackSize();
	//std::cout << luaL_tolstring(mclass->m_lua, -1, NULL) << std::endl;
	//std::cout << "Get: " << mclass->LuaGet<char*>() << std::endl;
	//mclass->PrintStackSize();
	//mclass->LuaPush<double>(1.1324);
	//mclass->PrintStackSize();
	//std::cout << luaL_tolstring(mclass->m_lua, -1, NULL) << std::endl;
	//mclass->PrintStackSize();
	
	TestLua_1* mclass = new TestLua_1();
	mclass->Test();
	return 0;

}