#include "LuaClass.h"

LuaClass::LuaClass(): m_lua(NULL)
{

}

LuaClass::~LuaClass()
{
	// ���m_lua��Ϊ��,��close
	if (m_lua)
	{
		lua_close(m_lua);
	}
}

bool LuaClass::CreateLuaState()
{
	
	m_lua = luaL_newstate();
	if (m_lua == NULL)
	{
		printf("error Lua��ʼ������ʧ��! �����쳣...\n");
		return false;
	}
	luaL_openlibs(m_lua);
	return true;
	

}

void LuaClass::PrintStackSize(char* tag)
{
	if (tag)
	{
		std::cout << "��ջ��С----> " << tag << ": " << lua_gettop(m_lua) << std::endl;
	}
	else
	{
		std::cout << "��ջ��С----> " << lua_gettop(m_lua) << std::endl;
	}
}

void LuaClass::PrintStack(char* tag)
{
	int size_ = lua_gettop(m_lua);

	if (tag)
	{
		std::cout << "   ******" << tag << "******"  << std::endl;
	}
	printf("L:0x%x\n", m_lua);
	printf("size:%d\n",size_);
	for (int i = 1; i <= size_; i++)
	{
		
		printf("[%d](%s):%s\n", i, luaL_typename(m_lua, i), luaL_tolstring(m_lua,i,NULL));
		lua_pop(m_lua, 1); // ���� luaL_tolstring �Ὣ���������ջ,���ｫ��������
	}
	printf("\n\n");
	
}

bool LuaClass::dofile(const char* f)
{
	if (f == NULL)
	{
		return false;
	}
	// luaL_dofile(L,�ļ���) ʧ�ܷ��ط�0ֵ,����ֵ�ַ�������ջ��, �����Ͽ�������ȷ�˷���0���Ҳ��ı��ջ
	if (luaL_dofile(m_lua, f) != 0)
	{
		
		const char* errostr = lua_tostring(m_lua, -1);
		//std::cout << "luaL_dofile: " << errostr << std::endl;
		throw std::logic_error(errostr);
		lua_pop(m_lua, 1);// ������ջ��������
		return false;
	} 
	else
	{
		std::cout << "�ɹ����ļ�: " << f << std::endl;
		return true;
	}
}

bool LuaClass::dostring(const char* s)
{
	if (s == NULL)
	{
		return false;
	}
	// ���ﷵ��ֵ�����������,���ط�0 ��ʾ����
	if (luaL_dostring(m_lua, s) != 0)
	{
		const char* errostr = lua_tostring(m_lua, -1);
		//std::cout << "luaL_dostringʧ��: " << errostr << std::endl;
		throw std::logic_error(errostr);
		lua_pop(m_lua, 1);// ������ջ��������
		return false;


	}
	//std::cout << "�ɹ����ļ�: " << s << std::endl;
	return true;

}






