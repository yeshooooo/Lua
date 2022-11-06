#pragma once
#include <iostream>
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
	template<>
	char* LuaGet<char*>(int index) {
		if (!LuaCheck<char*>(index))
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		return (char*)lua_tostring(m_lua, index);
	}
	template<>
	std::string LuaGet<std::string>(int index) {
		if (!LuaCheck<std::string>(index))
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		std::string tmpstr = (char*)lua_tostring(m_lua, index);
		return std::move(tmpstr);
	}
	template<>
	int LuaGet<int>(int index) {
		if (!LuaCheck<int>(index))
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		return lua_tonumber(m_lua, index);
	}
	template<>
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
		if (!LuaCheck<char*>())
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		char* tmp = (char*)lua_tostring(m_lua, -1);

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
		if (!LuaCheck<std::string>())
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		std::string tmpstr = (char*)lua_tostring(m_lua, -1);

		if (_pop)
		{
			lua_pop(m_lua, 1);
		} 
		return std::move(tmpstr);
	}
	template<>
	int LuaGetGlobal<int>(const char* global, bool _pop) {
		if (GetGlobal(global) == false)
		{
			std::cout << "erro check! ��ȡȫ�ֱ��� :" << global << "ʧ��" << std::endl;
		}
		if (!LuaCheck<int>())
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		int tmp = lua_tonumber(m_lua, -1);
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
		if (!LuaCheck<double>())
		{
			std::cout << "err check, ���ʧ��" << std::endl;
		}
		double tmp =  lua_tonumber(m_lua, -1);
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
public:
	// Ϊ�˷������,��Ϊ���е�
	lua_State* m_lua;
private:
//	lua_State* m_lua;
};

