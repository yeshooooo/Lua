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
	// ��ʼ��lua����
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

	// _________________�ػ�get-----------
	//����
	template<typename _Ty>
	inline _Ty LuaGet(int index = -1, bool _pop = false) 
	{
		return LuaHelp::LuaGet<_Ty>(GetLuaState(), index, _pop);
	}

	//// �ػ��ַ�������
	//template<> inline
	//char* LuaGet<char*>(int index, bool _pop) {
	//	if (!LuaCheck<char*>(index))
	//	{
	//		/*std::cout << "err check, ���ʧ��" << std::endl;*/
	//		throw std::logic_error("err check, ���ʧ�ܣ��׳��Զ����쳣");
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
	//		throw std::logic_error("err check, ���ʧ�ܣ��׳��Զ����쳣");
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
	//		//std::cout << "err check, ���ʧ��" << std::endl;
	//		throw std::logic_error("err check, ���ʧ�ܣ��׳��Զ����쳣");
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
	//		throw std::logic_error("err check, ���ʧ�ܣ��׳��Զ����쳣");
	//	}
	//	double tmp = lua_tonumber(m_lua, index);
	//	if (_pop)
	//	{
	//		// 
	//		lua_remove(m_lua, index);
	//	}
	//	return tmp;
	//}
	// _________________�ػ�check-----------
	//����
	template<typename _Ty>
	bool LuaCheck(int index = -1)
	{
		return LuaHelp::LuaCheck<_Ty>(GetLuaState(), index);
	}

	//// �ػ��ַ�������
	//template<>
	//bool LuaCheck<char*>(int index) {
	//	return lua_isstring(m_lua,index) == 0 ? false : true; //����Ƿ����ַ���
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
	// -----------------�ػ�push---------------
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

	//---------------�ػ� get ��ȡȫ�ֱ���----------------------
	template<typename _Ty>
	_Ty LuaGetGlobal(const char* global, bool _pop = true) {
		if (GetGlobal(global) == false)
		{
			//std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
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
	// �����Ż�����Ҫ�ػ�
	//template<>
	//char* LuaGetGlobal<char*>(const char* global, bool _pop) {
	//	if (GetGlobal(global) == false)
	//	{
	//		//std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
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
	//		//std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
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
	//		//std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
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
	//		//std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
	//		throw std::logic_error("LuaGetGlobal erro");
	//	}

	//	double tmp =  LuaGet<double>();
	//	if (_pop)
	//	{
	//		lua_pop(m_lua, 1);
	//	}
	//	return tmp;
	//}

	//---------------�ػ� set ����ȫ�ֱ���----------------------
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
	//		std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
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
	//		std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
	//		return false;
	//	}
	//	return true;

	//}
	//template<>
	//bool LuaSetGlobal<int>(int data, const char* global) {
	//	lua_pushnumber(m_lua, data);
	//	if (SetGlobal(global) == false)
	//	{
	//		std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
	//		return false;
	//	}
	//	return true;

	//}

	//template<>
	//bool LuaSetGlobal<double>(double data, const char* global) {
	//	lua_pushnumber(m_lua, data);
	//	if (SetGlobal(global) == false)
	//	{
	//		std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
	//		return false;
	//	}
	//	return true;

	//}

///// <summary>
///// ����Lua����ģ��
///// 	c++11 ��ֻ���õݹ���������б�
///// </summary>
///// 		template<typename _FirstArg, typename... _Args>
//#if 0
//	inline void CallLua(int& argSize) // ѹ���޲���
//	{
//		std::cout << "void" << std::endl;
//	}
//
//
//	template<typename _FirstArg, typename... _Args>
//	void CallLua(int& argSize,_FirstArg arg1, _Args...args) // ѹ�����
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
//			int argSize = 0; // ������ʽ
//			CallLua(argSize,args...);
//			if (lua_pcall(m_lua, argSize, 1, 0) != 0)
//			{
//				lua_pop(GetLuaState(), 1); //��������ֵ
//				/*PrintStack("lua_pcall erro");*/
//				throw std::logic_error("lua_pcall erro"); //�׳��쳣
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
	////////////////////////////////����Lua����ģ��//////////////////////////////////////////

	inline void __CallLua(int& argSize)//ѹ���޲���
	{
		//std::cout << "VOID" << std::endl;
	}

	template<typename _FirstArg, typename... _Args>
	void __CallLua(int& argSize, _FirstArg arg1, _Args...args)//ѹ�����
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
			int argSize = 0;//��������
			__CallLua(argSize, args...);
			PrintStack();
			//std::cout << "��������:" << argSize << std::endl;
			if (lua_pcall(m_lua, argSize, 1, 0) != 0)
			{
				lua_pop(GetLuaState(), 1);//��������ֵ 
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
	//		int argSize = 0;//��������
	//		CallLua(argSize, args...);
	//		PrintStack();
	//		//cout << "��������:" << argSize << endl;
	//		if (lua_pcall(m_lua, argSize, 1, 0) != 0)
	//		{
	//			lua_pop(GetLuaState(), 1);//��������ֵ 
	//			throw std::logic_error("lua_pcall erro");
	//		}
	//		_Ret t = LuaGet<_Ret>();
	//		lua_pop(m_lua, 1);
	//		return t;


	//	}



	//	return _Ret();
	//}

/// <summary>
/// �޲���CALL
/// </summary>

	template<typename... _Args>
	LuaClass& VoidCallLuaFunction(char* FunctionName, _Args...args)
	{

		if (GetGlobal(FunctionName))
		{
			int argSize = 0;//��������
			__CallLua(argSize, args...);
			PrintStack();
			//std::cout << "��������:" << argSize << std::endl;
			if (lua_pcall(m_lua, sizeof...(args), 0, 0) != 0) //����ǿ�ưѷ���ֵдΪ0����lua�Ｔʹ�з���ֵ������Ҳ������
			{
				lua_pop(GetLuaState(), 1);//��������ֵ 
				throw std::logic_error("GetGlobal erro");
			}
			return *this;


		}
		throw std::logic_error("AutoCallLuaFunction GetGlobal erro");

	}

	/// <summary>
	/// �Զ�CALL
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
			int argSize = 0;//��������
			__CallLua(argSize, args...);
			PrintStack();
			//std::cout << "��������:" << argSize << std::endl;
			if (lua_pcall(m_lua, sizeof...(args), -1, 0) != 0) //����ǿ�ưѷ���ֵдΪ0����lua�Ｔʹ�з���ֵ������Ҳ������
			{
				lua_pop(GetLuaState(), 1);//��������ֵ 
				throw std::logic_error("GetGlobal erro");
			}
			return *this;


		}
		throw std::logic_error("AutoCallLuaFunction GetGlobal erro");

	}


	// -------------------------��ȡ�෵��ֵ-------------
	template<typename... _Args>
	std::vector<LuaData> GetResult(_Args...args)
	{
		int _argsize = sizeof...(args); // �����_argsize�������ڼ��㣬�������������ʼ��
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
				throw std::logic_error("�޷���ȡ����ֵ��δ֪������");
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
	// Ϊ�˷������,��Ϊ���е�
	//lua_State* m_lua;
private:
	lua_State* m_lua;
};

