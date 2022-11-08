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
	//��ʼ��Lua����
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


	////////////////////////////////��ȡ�෵��ֵ//////////////////////////////////////////
	template< typename... _Args>
	 vector<LuaData> GetResult(_Args...args)
	{
		auto tmp = std::move(LuaHelp::GetResult(m_lua, args...));
		return tmp;
	}

	///////////////////////////////�ػ�Get///////////////////////////////////////////
	template<typename _Ty>
	inline _Ty LuaGet(int index = -1, bool _pop = false)
	{
		return LuaHelp::LuaGet<_Ty>(GetLuaState(), index, _pop);
	}
	///////////////////////////////�ػ�Check///////////////////////////////////////////
	template<typename _Ty>
	inline bool LuaCheck(int index = -1)
	{
		return LuaHelp::LuaCheck<_Ty>(index);
	}
	//////////////////////////////////�ػ�Push////////////////////////////////////////
	template<typename _Type>
	inline void LuaPush(_Type data)
	{
		LuaHelp::LuaPush<_Type>(GetLuaState(), data);
	} 
	//////////////////////////////�ػ� ��ȡȫ�ֱ���////////////////////////////////////////////
	template<typename _Ty>
	inline _Ty LuaGetGlobal(char*global, bool _pop = true)
	{
		return LuaHelp::LuaGetGlobal<_Ty>(GetLuaState(), global, _pop);
	}

	//////////////////////////////�ػ� ����ȫ�ֱ���////////////////////////////////////////////
	template<typename _Ty>
	inline bool LuaSetGlobal(_Ty data, char*global)
	{
		return LuaHelp::LuaSetGlobal<_Ty>(m_lua, data, global);
	}
	
	////////////////////////////////����Lua����ģ��//////////////////////////////////////////

	 
	template<typename _Ret, typename... _Args>
	inline _Ret OneCallLuaFuction(char* FunctionName, _Args...args)
	{
	 
		return LuaHelp::OneCallLuaFuction<_Ret>(GetLuaState(), FunctionName, args...);
 
	}

	 
	 //////////////////////////////////�޲���CALL////////////////////////////////////////
	template< typename... _Args>
	inline LuaClass& VoidCallLuaFuction(char* FunctionName, _Args...args)
	{
		LuaHelp::VoidCallLuaFuction(GetLuaState(), FunctionName, args...);
		return *this;
	}

 
	//////////////////////////////////�Զ�CALL////////////////////////////////////////
	template< typename... _Args>
	inline LuaClass& AutoCallLuaFuction(char* FunctionName, _Args...args)
	{
		LuaHelp::AutoCallLuaFuction(GetLuaState(), FunctionName, args...);
		return *this;
	}

	

private:
	lua_State* m_lua;
};

