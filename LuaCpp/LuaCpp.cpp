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

template<typename Ty>
Ty mget();

template<> inline
int mget<int>() {
	
	return 888; //这里为了方便每次返回888
}
template<> inline	
char*  mget<char*>() {
	return "Hello";
}
inline void MyPrint(int arg)
{
	std::cout << arg << std::endl;
}
inline void MyPrint( char* arg) {
	std::cout << " char* :" << std::endl;
	std::cout << arg << std::endl;
}

inline void MyPrint()
{
	std::cout << "void" << std::endl;
}

template<typename First, typename... _Args>
inline void MyPrint(int& callCount, First f, _Args...args)
{
	std::cout << __FUNCDNAME__ << std::endl;
	callCount++;
	MyPrint(f);
	MyPrint(callCount ,args...); // 递归调用自己
}

// 这种方式在有返回值的上层函数中使用，因为递归调用中不能有返回值
#if 1
template<typename _Ret,typename... _Args>
inline _Ret Call_Print(_Args...args)
{
	std::cout << "Call_Print" << std::endl;
	int callCount = 0;
	MyPrint(callCount,args...);
	std::cout << "callCount: " << callCount << std::endl;
	_Ret rt;
	rt = mget<_Ret>();

	return rt;
}
#endif
#if 0
template< typename... _Args>
inline void Call_Print(_Args...args)
{
	std::cout << "Call_Print" << std::endl;
	MyPrint(args...);
}
#endif
int main()
{
	auto ret = Call_Print<char*>(1, 2, 3);
	std::cout << "ret: " << ret << std::endl;
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
	
	//TestLua_1* mclass = new TestLua_1();
	//mclass->Test();
	//MyPrint(1, 2, 3);
	//MyPrint();
	//Call_Print(1, 2, (char*)"11");
	return 0;

}