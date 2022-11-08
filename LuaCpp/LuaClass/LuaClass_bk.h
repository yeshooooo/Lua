#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include "lua.hpp"
#include "LuaHelp.h"

union LuaData
{
	int IntData;
	double numberData;
	char* StrData;

};

//typedef struct __LuaData
//{
//	LuaDataTmp data;
//}LuaData, *PLuaData;

enum LuaType
{
	LuaInt = 0,
	LuaDouble,
	LuaString

};


class LuaClass
{
public:
	LuaClass();
	~LuaClass();
	// 初始化lua环境
	bool CreateLuaState();
	// 
	void PrintStackSize(char* tag = NULL);
	void PrintStack(char* tag = NULL);
	//
	bool dofile(const char* f);
	bool dostring(const char* s);
	//
	bool GetGlobal(const char* name)
	{
		return LuaHelp::GetGlobal(m_lua, name);
	}
	bool SetGlobal(const char* name)
	{
		return LuaHelp::SetGlobal(m_lua, name);
	}

	// _________________特化get-----------
	//定义
	template<typename _Ty>
	inline _Ty LuaGet(int index = -1, bool _pop = false) 
	{
		return LuaHelp::LuaGet<_Ty>(GetLuaState(), index, _pop);
	}

	//// 特化字符串类型
	//template<> inline
	//char* LuaGet<char*>(int index, bool _pop) {
	//	if (!LuaCheck<char*>(index))
	//	{
	//		/*std::cout << "err check, 检查失败" << std::endl;*/
	//		throw std::logic_error("err check, 检查失败，抛出自定义异常");
	//	}
	//	char* tmp =  (char*)lua_tostring(m_lua, index);
	//	if (_pop)
	//	{
	//		// 
	//		lua_remove(m_lua, index);
	//	}
	//	return tmp;
	//}
	//template<> inline
	//std::string LuaGet<std::string>(int index, bool _pop) {
	//	if (!LuaCheck<std::string>(index))
	//	{
	//		throw std::logic_error("err check, 检查失败，抛出自定义异常");
	//	}
	//	std::string tmpstr = (char*)lua_tostring(m_lua, index);
	//	if (_pop)
	//	{
	//		// 
	//		lua_remove(m_lua, index);
	//	}
	//	return std::move(tmpstr);
	//}
	//template<> inline
	//int LuaGet<int>(int index, bool _pop) {
	//	if (!LuaCheck<int>(index))
	//	{
	//		//std::cout << "err check, 检查失败" << std::endl;
	//		throw std::logic_error("err check, 检查失败，抛出自定义异常");
	//	}
	//	int tmp = lua_tonumber(m_lua, index);
	//	if (_pop)
	//	{
	//		// 
	//		lua_remove(m_lua, index);
	//	}
	//	return tmp;
	//}
	//template<> inline
	//double LuaGet<double>(int index, bool _pop) {
	//	if (!LuaCheck<double>(index))
	//	{
	//		throw std::logic_error("err check, 检查失败，抛出自定义异常");
	//	}
	//	double tmp = lua_tonumber(m_lua, index);
	//	if (_pop)
	//	{
	//		// 
	//		lua_remove(m_lua, index);
	//	}
	//	return tmp;
	//}
	// _________________特化check-----------
	//定义
	template<typename _Ty>
	bool LuaCheck(int index = -1)
	{
		return LuaHelp::LuaCheck<_Ty>(GetLuaState(), index);
	}

	//// 特化字符串类型
	//template<>
	//bool LuaCheck<char*>(int index) {
	//	return lua_isstring(m_lua,index) == 0 ? false : true; //检查是否是字符串
	//}
	//template<>
	//bool LuaCheck<std::string>(int index) {
	//	return lua_isstring(m_lua, index) == 0 ? false : true;
	//}
	//template<>
	//bool LuaCheck<int>(int index) {
	//	return lua_isnumber(m_lua, index) == 0 ? false : true;
	//}
	//template<>
	//bool LuaCheck<double>(int index) {
	//	return lua_isnumber(m_lua, index) == 0 ? false : true;
	//}
	// -----------------特化push---------------
	template <typename _Ty>
	inline void LuaPush(_Ty data)
	{
		return LuaHelp::LuaPush<_Ty>(GetLuaState(), data);
	}

	//template<> void LuaPush<char*>(char* t) {
	//	lua_pushstring(m_lua, t);
	//}

	//template<> void LuaPush<const char*>(const char* t) {
	//	lua_pushstring(m_lua, t);
	//}

	//template<> void LuaPush<std::string>(std::string t) {
	//	lua_pushstring(m_lua, t.c_str());
	//}
	//template<> void LuaPush<int>(int t) {
	//	lua_pushnumber(m_lua, t);
	//}

	//template<> void LuaPush<double>(double t) {
	//	lua_pushnumber(m_lua, t);
	//}

	//---------------特化 get 获取全局变量----------------------
	template<typename _Ty>
	_Ty LuaGetGlobal(const char* global, bool _pop = true) {
		if (GetGlobal(global) == false)
		{
			//std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
			throw std::logic_error("LuaGetGlobal erro");
		}

		_Ty tmp = LuaGet<_Ty>();
		//char* tmp = (char*)lua_tostring(m_lua, -1);

		if (_pop)
		{
			lua_pop(m_lua, 1);

		}
		return tmp;


	}
	// 这里优化后不需要特化
	//template<>
	//char* LuaGetGlobal<char*>(const char* global, bool _pop) {
	//	if (GetGlobal(global) == false)
	//	{
	//		//std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		throw std::logic_error("LuaGetGlobal erro");
	//	}

	//	char* tmp =  LuaGet<char*>();
	//	//char* tmp = (char*)lua_tostring(m_lua, -1);

	//	if (_pop)
	//	{
	//		lua_pop(m_lua, 1);

	//	} 
	//	return tmp;
	//		
	//}
	//template<>
	//std::string LuaGetGlobal<std::string>(const char* global, bool _pop) {
	//	if (GetGlobal(global) == false)
	//	{
	//		//std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		throw std::logic_error("LuaGetGlobal erro");
	//	}

	//	std::string tmp = LuaGet<std::string>();

	//	if (_pop)
	//	{
	//		lua_pop(m_lua, 1);
	//	} 
	//	return std::move(tmp);
	//}
	//template<>
	//int LuaGetGlobal<int>(const char* global, bool _pop) {
	//	if (GetGlobal(global) == false)
	//	{
	//		//std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		throw std::logic_error("LuaGetGlobal erro");
	//	}

	//	int tmp = LuaGet<int>();
	//	if (_pop)
	//	{
	//		lua_pop(m_lua, 1);
	//	}
	//	return tmp;
	//}
	//template<>
	//double LuaGetGlobal<double>(const char* global, bool _pop) {
	//	if (GetGlobal(global) == false)
	//	{
	//		//std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		throw std::logic_error("LuaGetGlobal erro");
	//	}

	//	double tmp =  LuaGet<double>();
	//	if (_pop)
	//	{
	//		lua_pop(m_lua, 1);
	//	}
	//	return tmp;
	//}

	//---------------特化 set 设置全局变量----------------------
	template<typename _Ty>
	bool LuaSetGlobal(_Ty data, const char* global) {
		LuaPush<_Ty>(data);
		if (SetGlobal(global) == false)
		{
			throw std::logic_error("LuaSetGlobal erro");
			return false;
		}
		return true;
	}

	//template<>
	//bool LuaSetGlobal<char*>(char* data, const char* global) {

	//	lua_pushstring(m_lua, data);
	//	if (SetGlobal(global) == false)
	//	{
	//		std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		return false;
	//	}
	//	return true;
	//	
	//}
	//template<>
	//bool LuaSetGlobal<std::string >(std::string data, const char* global) {
	//	lua_pushstring(m_lua, data.c_str());
	//	if (SetGlobal(global) == false)
	//	{
	//		std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		return false;
	//	}
	//	return true;

	//}
	//template<>
	//bool LuaSetGlobal<int>(int data, const char* global) {
	//	lua_pushnumber(m_lua, data);
	//	if (SetGlobal(global) == false)
	//	{
	//		std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		return false;
	//	}
	//	return true;

	//}

	//template<>
	//bool LuaSetGlobal<double>(double data, const char* global) {
	//	lua_pushnumber(m_lua, data);
	//	if (SetGlobal(global) == false)
	//	{
	//		std::cout << "erro check! 获取全局变量 :" << global << "失败" << std::endl;
	//		return false;
	//	}
	//	return true;

	//}

///// <summary>
///// 调用Lua函数模板
///// 	c++11 中只能用递归遍历参数列表
///// </summary>
///// 		template<typename _FirstArg, typename... _Args>
//#if 0
//	inline void CallLua(int& argSize) // 压入无参数
//	{
//		std::cout << "void" << std::endl;
//	}
//
//
//	template<typename _FirstArg, typename... _Args>
//	void CallLua(int& argSize,_FirstArg arg1, _Args...args) // 压入参数
//	{
//		argSize++;
//		LuaPush<_FirstArg>(arg1);
//		
//		CallLua(argSize ,args...);
//	}
//
//
//	template<typename _Ret,typename... _Args>
//	_Ret CallLuaFunction(char* FunctionName, _Args...args)
//	{
//		_Ret t;
//		if (GetGlobal(FunctionName))
//		{
//			int argSize = 0; // 参数格式
//			CallLua(argSize,args...);
//			if (lua_pcall(m_lua, argSize, 1, 0) != 0)
//			{
//				lua_pop(GetLuaState(), 1); //弹出错误值
//				/*PrintStack("lua_pcall erro");*/
//				throw std::logic_error("lua_pcall erro"); //抛出异常
//			}
//			t = LuaGet<_Ret>();
//			//if (_pop)
//			//{
//			//	lua_pop(m_lua, 1);
//			//}
//			_Ret t = LuaGet<_Ret>();
//			return t;
//		}
//		return _Ret();
//
//	}
//
//#endif
	////////////////////////////////调用Lua函数模板//////////////////////////////////////////

	inline void __CallLua(int& argSize)//压入无参数
	{
		//std::cout << "VOID" << std::endl;
	}

	template<typename _FirstArg, typename... _Args>
	void __CallLua(int& argSize, _FirstArg arg1, _Args...args)//压入参数
	{
		//std::cout << "push" << std::endl;
		argSize++;
		LuaPush<_FirstArg>(arg1);
		__CallLua(argSize, args...);
	}

	template<typename _Ret, typename... _Args>
	_Ret OneCallLuaFunction(char* FunctionName, _Args...args)
	{
		
		if (GetGlobal(FunctionName))
		{
			int argSize = 0;//参数个数
			__CallLua(argSize, args...);
			PrintStack();
			//std::cout << "参数个数:" << argSize << std::endl;
			if (lua_pcall(m_lua, argSize, 1, 0) != 0)
			{
				lua_pop(GetLuaState(), 1);//弹出错误值 
				throw std::logic_error("lua_pcall erro");
			}
			_Ret t = LuaGet<_Ret>();
			lua_pop(m_lua, 1);
			return t;

		}



		return _Ret();
	}


	//template<typename _Ret, typename... _Args>
	//_Ret CallLuaFuctionPop(char* FunctionName, _Args...args)
	//{
	//	if (GetGlobal(FunctionName))
	//	{
	//		int argSize = 0;//参数个数
	//		CallLua(argSize, args...);
	//		PrintStack();
	//		//cout << "参数个数:" << argSize << endl;
	//		if (lua_pcall(m_lua, argSize, 1, 0) != 0)
	//		{
	//			lua_pop(GetLuaState(), 1);//弹出错误值 
	//			throw std::logic_error("lua_pcall erro");
	//		}
	//		_Ret t = LuaGet<_Ret>();
	//		lua_pop(m_lua, 1);
	//		return t;


	//	}



	//	return _Ret();
	//}

/// <summary>
/// 无参数CALL
/// </summary>

	template<typename... _Args>
	LuaClass& VoidCallLuaFunction(char* FunctionName, _Args...args)
	{

		if (GetGlobal(FunctionName))
		{
			int argSize = 0;//参数个数
			__CallLua(argSize, args...);
			PrintStack();
			//std::cout << "参数个数:" << argSize << std::endl;
			if (lua_pcall(m_lua, sizeof...(args), 0, 0) != 0) //这里强制把返回值写为0，即lua里即使有返回值，我们也不接受
			{
				lua_pop(GetLuaState(), 1);//弹出错误值 
				throw std::logic_error("GetGlobal erro");
			}
			return *this;


		}
		throw std::logic_error("AutoCallLuaFunction GetGlobal erro");

	}

	/// <summary>
	/// 自动CALL
	/// </summary>
	/// <typeparam name="..._Args"></typeparam>
	/// <param name="FunctionName"></param>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<typename... _Args>
	LuaClass& AutoCallLuaFunction(char* FunctionName, _Args...args)
	{

		if (GetGlobal(FunctionName))
		{
			int argSize = 0;//参数个数
			__CallLua(argSize, args...);
			PrintStack();
			//std::cout << "参数个数:" << argSize << std::endl;
			if (lua_pcall(m_lua, sizeof...(args), -1, 0) != 0) //这里强制把返回值写为0，即lua里即使有返回值，我们也不接受
			{
				lua_pop(GetLuaState(), 1);//弹出错误值 
				throw std::logic_error("GetGlobal erro");
			}
			return *this;


		}
		throw std::logic_error("AutoCallLuaFunction GetGlobal erro");

	}


	// -------------------------获取多返回值-------------
	template<typename... _Args>
	std::vector<LuaData> GetResult(_Args...args)
	{
		int _argsize = sizeof...(args); // 这里的_argsize可以用于计算，不能用于数组初始化
		int argarray[sizeof...(args)] = { args... };
		std::cout << _argsize << std::endl;
		std::vector<LuaData> __array = {};
		int __index = -_argsize + 1;
		for (auto v: argarray)
		{
			LuaData temp = { 0 };
			std::cout << "v: " << v << std::endl;
			switch (v)
			{
			case LuaType::LuaInt:
				temp.IntData = LuaGet<int>(-1 + __index);
				__array.push_back(temp);
				break;
			case LuaType::LuaDouble:
				temp.numberData = LuaGet<double>(-1 + __index);
				__array.push_back(temp);
				break;
			case LuaType::LuaString:
				temp.StrData =  LuaGet<char*>(-1 + __index);
				__array.push_back(temp);
				break;
			default:
				throw std::logic_error("无法获取返回值，未知的类型");
				break;
			}
			__index++;
		}

		lua_pop(m_lua, _argsize);
		return __array;
	}


public:
	inline lua_State* LuaClass::GetLuaState()
	{
		return m_lua;
	}
	// 为了方便测试,变为共有的
	//lua_State* m_lua;
private:
	lua_State* m_lua;
};

