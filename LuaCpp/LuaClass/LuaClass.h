#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "lua.hpp"
#include "LuaHelp.h"
using namespace std;
class LuaClass
{
public:
	//初始化Lua环境
	bool CreateLuaState();
	void PrintStackSize(char* tag = NULL);
	void PrintStack(char* tag = NULL);
	bool dofile(char* f);
	bool dostring(char* f);
	inline bool GetGlobal(char* name) { return LuaHelp::GetGlobal(m_lua, name); }
	inline bool SetGlobal(char* name) { return LuaHelp::SetGlobal(m_lua, name); }

	inline lua_State* LuaClass::GetLuaState()
	{
		return m_lua;
	}
	
	LuaClass();
	~LuaClass();


	////////////////////////////////获取多返回值//////////////////////////////////////////
	template< typename... _Args>
	 vector<LuaData> GetResult(_Args...args)
	{
		auto tmp = std::move(LuaHelp::GetResult(m_lua, args...));
		return tmp;
	}

	///////////////////////////////特化Get///////////////////////////////////////////
	template<typename _Ty>
	inline _Ty LuaGet(int index = -1, bool _pop = false)
	{
		return LuaHelp::LuaGet<_Ty>(GetLuaState(), index, _pop);
	}
	///////////////////////////////特化Check///////////////////////////////////////////
	template<typename _Ty>
	inline bool LuaCheck(int index = -1)
	{
		return LuaHelp::LuaCheck<_Ty>(index);
	}
	//////////////////////////////////特化Push////////////////////////////////////////
	template<typename _Type>
	inline void LuaPush(_Type data)
	{
		LuaHelp::LuaPush<_Type>(GetLuaState(), data);
	} 
	//////////////////////////////特化 获取全局变量////////////////////////////////////////////
	template<typename _Ty>
	inline _Ty LuaGetGlobal(char*global, bool _pop = true)
	{
		return LuaHelp::LuaGetGlobal<_Ty>(GetLuaState(), global, _pop);
	}

	//////////////////////////////特化 设置全局变量////////////////////////////////////////////
	template<typename _Ty>
	inline bool LuaSetGlobal(_Ty data, char*global)
	{
		return LuaHelp::LuaSetGlobal<_Ty>(m_lua, data, global);
	}
	
	////////////////////////////////调用Lua函数模板//////////////////////////////////////////

	 
	template<typename _Ret, typename... _Args>
	inline _Ret OneCallLuaFuction(char* FunctionName, _Args...args)
	{
	 
		return LuaHelp::OneCallLuaFuction<_Ret>(GetLuaState(), FunctionName, args...);
 
	}

	 
	 //////////////////////////////////无参数CALL////////////////////////////////////////
	template< typename... _Args>
	inline LuaClass& VoidCallLuaFuction(char* FunctionName, _Args...args)
	{
		LuaHelp::VoidCallLuaFuction(GetLuaState(), FunctionName, args...);
		return *this;
	}

 
	//////////////////////////////////自动CALL////////////////////////////////////////
	template< typename... _Args>
	inline LuaClass& AutoCallLuaFuction(char* FunctionName, _Args...args)
	{
		LuaHelp::AutoCallLuaFuction(GetLuaState(), FunctionName, args...);
		return *this;
	}

	

private:
	lua_State* m_lua;
};

