//面向过程
#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "lua.hpp"
using namespace std;

union LuaData
{
	int IntData;
	double numberData;
	char* StrData;
};


enum LuaType
{
	LuaInt = 0,
	LuaDouble,
	LuaString
};
namespace LuaHelp {

	bool GetGlobal(lua_State* m_lua, char* name);
	bool SetGlobal(lua_State* m_lua, char* name);

	void PrintStack(lua_State* m_lua, char* tag = NULL);
	///////////////////////////////特化Check///////////////////////////////////////////
	template<typename _Ty>
	bool LuaCheck(lua_State* m_lua, int index = -1);
	template<> inline	bool LuaCheck<char*>(lua_State* m_lua, int index)//检查是否是字符串
	{
		return lua_isstring(m_lua, index) == 0 ? false : true;
	}

	template<>	inline bool LuaCheck<string>(lua_State* m_lua, int index)
	{
		return lua_isstring(m_lua, index) == 0 ? false : true;
	}

	template<> inline	bool LuaCheck<int>(lua_State* m_lua, int index)
	{
		return lua_isnumber(m_lua, index) == 0 ? false : true;
	}

	template<>	inline bool LuaCheck<double>(lua_State* m_lua, int index)
	{
		return lua_isnumber(m_lua, index) == 0 ? false : true;
	}

	template<>	inline bool LuaCheck<float>(lua_State* m_lua, int index)
	{
		return lua_isnumber(m_lua, index) == 0 ? false : true;
	}


	///////////////////////////////特化Get///////////////////////////////////////////
	template<typename _Ty>
	_Ty LuaGet(lua_State* m_lua, int index = -1, bool _pop = false);
	template<> inline	char* LuaGet<char*>(lua_State* m_lua, int index, bool _pop)
	{
		if (!LuaCheck<char*>(m_lua, index))
		{
			throw std::logic_error("erro check!");
		}
		char* tmp = (char*)lua_tostring(m_lua, index);
		if (_pop)
		{
			lua_remove(m_lua, index);
		}
		return tmp;
	}
	template<> inline string LuaGet<string>(lua_State* m_lua, int index, bool _pop)
	{
		if (!LuaCheck<char*>(m_lua, index))
		{
			throw std::logic_error("erro check!");
		}

		string tmpstr = (char*)lua_tostring(m_lua, index);
		if (_pop)
		{
			lua_remove(m_lua, index);
		}
		return std::move(tmpstr);
	}
	template<> inline int LuaGet<int>(lua_State* m_lua, int index /* = -1 */, bool _pop)
	{

		if (!LuaCheck<int>(m_lua, index))
		{
			throw std::logic_error("erro check!");//直接异常 
		}
		int  tmp = lua_tonumber(m_lua, index);
		if (_pop)
		{
			lua_remove(m_lua, index);
		}
		return  tmp;
	}
	template<> inline double LuaGet<double>(lua_State* m_lua, int index /* = -1 */, bool _pop)
	{

		if (!LuaCheck<double>(m_lua, index))
		{
			throw std::logic_error("erro check!");
		}

		double  tmp = lua_tonumber(m_lua, index);
		if (_pop)
		{
			lua_remove(m_lua, index);
		}
		return  tmp;
	}
	template<> inline float LuaGet<float>(lua_State* m_lua, int index /* = -1 */, bool _pop)
	{

		if (!LuaCheck<float>(m_lua, index))
		{
			throw std::logic_error("erro check!");
		}

		float  tmp = (float)lua_tonumber(m_lua, index);
		if (_pop)
		{
			lua_remove(m_lua, index);
		}
		return  tmp;
	}
	//////////////////////////////////特化Push////////////////////////////////////////
	template<typename _TY>
	void LuaPush(lua_State* m_lua, _TY);
	template<> inline void LuaPush<char*>(lua_State* m_lua, char* t)
	{
		lua_pushstring(m_lua, t);
	}

	template<> inline void LuaPush<const char*>(lua_State* m_lua, const char* t)
	{
		lua_pushstring(m_lua, t);
	}

	template<> inline void LuaPush<int>(lua_State* m_lua, int t)
	{
		lua_pushnumber(m_lua, t);
	}

	template<> inline void LuaPush<double>(lua_State* m_lua, double t)
	{
		lua_pushnumber(m_lua, t);
	}


	//////////////////////////////特化 获取全局变量////////////////////////////////////////////
	template<typename _Ty>
	_Ty LuaGetGlobal(lua_State* m_lua, char* global, bool _pop = true)
	{
		if (GetGlobal(m_lua, global) == false)
		{
			throw std::logic_error("LuaGetGlobal erro");
		}
		_Ty tmp = LuaGet<_Ty>(m_lua, -1, _pop);
		return tmp;
	}

	//////////////////////////////特化 设置全局变量////////////////////////////////////////////
	template<typename _Ty>
	bool LuaSetGlobal(lua_State* m_lua, _Ty data, char* global)
	{
		LuaPush<_Ty>(m_lua, data);
		if (SetGlobal(m_lua, global) == false)
		{
			throw std::logic_error("LuaSetGlobal erro");
			return false;
		}
		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////调用Lua函数模板//////////////////////////////////////////

	inline void __CallLua(lua_State* m_lua, int& argSize)//压入无参数
	{
		//cout << "VOID" << endl;
	}

	template<typename _FirstArg, typename... _Args>
	void __CallLua(lua_State* m_lua, int& argSize, _FirstArg arg1, _Args...args)//压入参数
	{
		//cout << "push" << endl;
		argSize++;
		LuaPush<_FirstArg>(m_lua, arg1);
		__CallLua(m_lua, argSize, args...);
	}

	template<typename _Ret, typename... _Args>
	_Ret OneCallLuaFuction(lua_State* m_lua, char* FunctionName, _Args...args)
	{


		if (GetGlobal(m_lua, FunctionName))
		{
			int argSize = 0;//参数个数
			__CallLua(m_lua, argSize, args...);
			PrintStack(m_lua);
			//cout << "参数个数:" << argSize << endl;
			if (lua_pcall(m_lua, argSize, 1, 0) != 0)
			{
				lua_pop(m_lua, 1);//弹出错误值 
				throw std::logic_error("lua_pcall erro");
			}
			_Ret t = LuaGet<_Ret>(m_lua);
			lua_pop(m_lua, 1);
			return t;

		}



		return _Ret();
	}


	//////////////////////////////////无参数CALL////////////////////////////////////////
	template< typename... _Args>
	void VoidCallLuaFuction(lua_State* m_lua, char* FunctionName, _Args...args)
	{


		if (GetGlobal(m_lua, FunctionName))
		{
			int argSize = 0;//参数个数
			__CallLua(m_lua, argSize, args...);
			PrintStack(m_lua);
			//cout << "参数个数:" << argSize << endl;
			if (lua_pcall(m_lua, sizeof...(args)/*argSize*/, 0/*-1*/, 0) != 0)
			{
				lua_pop(m_lua, 1);//弹出错误值 
				throw std::logic_error("lua_pcall erro");
			}

			return;
		}



		throw std::logic_error("AutoCallLuaFuction GetGlobal erro");
	}


	//////////////////////////////////自动CALL////////////////////////////////////////
	template< typename... _Args>
	void AutoCallLuaFuction(lua_State* m_lua, char* FunctionName, _Args...args)
	{


		if (GetGlobal(m_lua, FunctionName))
		{
			int argSize = 0;//参数个数
			__CallLua(m_lua, argSize, args...);
			PrintStack(m_lua);
			//cout << "参数个数:" << argSize << endl;
			if (lua_pcall(m_lua, sizeof...(args)/*argSize*/, -1, 0) != 0)
			{
				lua_pop(m_lua, 1);//弹出错误值 
				throw std::logic_error("lua_pcall erro");
			}
			return;



		}



		throw std::logic_error("AutoCallLuaFuction GetGlobal erro");
	}


	template< typename... _Args>
	vector<LuaData> GetResult(lua_State* m_lua, _Args...args)
	{
		int _argsize = sizeof...(args);
		int argarray[sizeof...(args)] = { args... };
		cout << _argsize << endl;
		vector<LuaData> __array = {};
		int __index = -_argsize + 1;
		for (int v : argarray)
		{
			LuaData tmp = { 0 };
			cout << "v:" << v << endl;
			switch (v)
			{
			case  LuaType::LuaInt:
				tmp.IntData = LuaGet<int>(m_lua, -1 + __index);
				__array.push_back(tmp);
				break;
			case  LuaType::LuaDouble:
				tmp.numberData = LuaGet<double>(m_lua, -1 + __index);
				__array.push_back(tmp);
				break;
			case  LuaType::LuaString:
				tmp.StrData = LuaGet<char*>(m_lua, -1 + __index);
				__array.push_back(tmp);
				break;
			default:
				throw std::logic_error("无法获取返回值,未知的类型");
				break;
			}
			__index++;
		}

		lua_pop(m_lua, _argsize);
		return __array;

	}

}