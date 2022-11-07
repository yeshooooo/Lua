#pragma once
#include <iostream>
#include <stdexcept>
#include "lua.hpp"
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
	bool GetGlobal(const char* name);
	bool SetGlobal(const char* name);

	// _________________�ػ�get-----------
	//����
	template<typename _Ty>
	_Ty LuaGet(int index = -1);

	// �ػ��ַ�������
	template<> inline
	char* LuaGet<char*>(int index) {
		if (!LuaCheck<char*>(index))
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		return (char*)lua_tostring(m_lua, index);
	}
	template<> inline
	std::string LuaGet<std::string>(int index) {
		if (!LuaCheck<std::string>(index))
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		std::string tmpstr = (char*)lua_tostring(m_lua, index);
		return std::move(tmpstr);
	}
	template<> inline
	int LuaGet<int>(int index) {
		if (!LuaCheck<int>(index))
		{
			//std::cout << "err check, ���ʧ��" << std::endl;
			throw std::logic_error("erro check!");
		}
		return lua_tonumber(m_lua, index);
	}
	template<> inline
	double LuaGet<double>(int index) {
		if (!LuaCheck<double>(index))
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		return lua_tonumber(m_lua, index);
	}
	// _________________�ػ�check-----------
	//����
	template<typename _Ty>
	bool LuaCheck(int index = -1);

	// �ػ��ַ�������
	template<>
	bool LuaCheck<char*>(int index) {
		return lua_isstring(m_lua,index) == 0 ? false : true; //����Ƿ����ַ���
	}
	template<>
	bool LuaCheck<std::string>(int index) {
		return lua_isstring(m_lua, index) == 0 ? false : true;
	}
	template<>
	bool LuaCheck<int>(int index) {
		return lua_isnumber(m_lua, index) == 0 ? false : true;
	}
	template<>
	bool LuaCheck<double>(int index) {
		return lua_isnumber(m_lua, index) == 0 ? false : true;
	}
	// -----------------�ػ�push---------------
	template <typename _TY>
	void LuaPush(_TY);

	template<> void LuaPush<char*>(char* t) {
		lua_pushstring(m_lua, t);
	}

	template<> void LuaPush<std::string>(std::string t) {
		lua_pushstring(m_lua, t.c_str());
	}
	template<> void LuaPush<int>(int t) {
		lua_pushnumber(m_lua, t);
	}

	template<> void LuaPush<double>(double t) {
		lua_pushnumber(m_lua, t);
	}

	//---------------�ػ� get ��ȡȫ�ֱ���----------------------
	template<typename _Ty>
	_Ty LuaGetGlobal(const char* global, bool _pop = true);

	template<>
	char* LuaGetGlobal<char*>(const char* global, bool _pop) {
		if (GetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
		}

		char* tmp =  LuaGet<char*>();
		//char* tmp = (char*)lua_tostring(m_lua, -1);

		if (_pop)
		{
			lua_pop(m_lua, 1);

		} 
		return tmp;
			
	}
	template<>
	std::string LuaGetGlobal<std::string>(const char* global, bool _pop) {
		if (GetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
		}

		std::string tmp = LuaGet<std::string>();

		if (_pop)
		{
			lua_pop(m_lua, 1);
		} 
		return std::move(tmp);
	}
	template<>
	int LuaGetGlobal<int>(const char* global, bool _pop) {
		if (GetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
		}

		int tmp = LuaGet<int>();
		if (_pop)
		{
			lua_pop(m_lua, 1);
		}
		return tmp;
	}
	template<>
	double LuaGetGlobal<double>(const char* global, bool _pop) {
		if (GetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
		}

		double tmp =  LuaGet<double>();
		if (_pop)
		{
			lua_pop(m_lua, 1);
		}
		return tmp;
	}

	//---------------�ػ� set ����ȫ�ֱ���----------------------
	template<typename _Ty>
	bool LuaSetGlobal(_Ty data, const char* global);

	template<>
	bool LuaSetGlobal<char*>(char* data, const char* global) {
		lua_pushstring(m_lua, data);
		if (SetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
			return false;
		}
		return true;
		
	}
	template<>
	bool LuaSetGlobal<std::string >(std::string data, const char* global) {
		lua_pushstring(m_lua, data.c_str());
		if (SetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
			return false;
		}
		return true;

	}
	template<>
	bool LuaSetGlobal<int>(int data, const char* global) {
		lua_pushnumber(m_lua, data);
		if (SetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
			return false;
		}
		return true;

	}

	template<>
	bool LuaSetGlobal<double>(double data, const char* global) {
		lua_pushnumber(m_lua, data);
		if (SetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
			return false;
		}
		return true;

	}

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

	inline void CallLua(int& argSize)//ѹ���޲���
	{
		std::cout << "VOID" << std::endl;
	}

	template<typename _FirstArg, typename... _Args>
	void CallLua(int& argSize, _FirstArg arg1, _Args...args)//ѹ�����
	{
		std::cout << "push" << std::endl;
		argSize++;
		LuaPush<_FirstArg>(arg1);
		CallLua(argSize, args...);
	}

	template<typename _Ret, typename... _Args>
	_Ret CallLuaFunction(char* FunctionName, _Args...args)
	{

		if (GetGlobal(FunctionName))
		{
			int argSize = 0;//��������
			CallLua(argSize, args...);
			PrintStack();
			std::cout << "��������:" << argSize << std::endl;
			if (lua_pcall(m_lua, argSize, 1, 0) != 0)
			{
				lua_pop(GetLuaState(), 1);//��������ֵ 
				throw std::logic_error("lua_pcall erro");
			}
			_Ret t = LuaGet<_Ret>();
			return t;

		}



		return _Ret();
	}


	template<typename _Ret, typename... _Args>
	_Ret CallLuaFuctionPop(char* FunctionName, _Args...args)
	{
		if (GetGlobal(FunctionName))
		{
			int argSize = 0;//��������
			CallLua(argSize, args...);
			PrintStack();
			cout << "��������:" << argSize << endl;
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

