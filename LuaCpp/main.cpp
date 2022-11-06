#include <lua.hpp>
#include <iostream>

lua_State* m_lua = NULL;

bool InitLua()
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
// ��ӡ��ǰ��ջ�Ĵ�С
// ���������ǩ��Ϊ�˿������ӡ�ķ���
// ���ұ���
void printStackSize(const char* tag)
{
	int sz = lua_gettop(m_lua); //��ȡ��ջ��С
	printf("stacksize: %d <%s>\n", sz, tag);


}

//luaL_dostring
// �ײ���luaL_loadstring() ��lua_pcall
void example1()
{
	printStackSize("emample1---");
	int ret = luaL_dostring(m_lua, "print('hello')");
	// ���ﷵ��ֵ�����������,���ط�0 ��ʾ����
	//int ret = luaL_dostring(m_lua, "return 1,2,3");
	std::cout << ret << std::endl;
	if (ret != 0) // ʧ�ܷ��ط�0ֵ��ʧ�ܵĴ�����ջ�������ַ�������
	{
		const char* errostr =  lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;
	}
	printStackSize("emample1---"); //��ʱջ��Ϊ����ֵ 1, 2, 3
}


// luaL_loadstring

void example2() {
	printStackSize("----example2");
	luaL_loadstring(m_lua, "print('Hello Lua')");
	printStackSize("----example2");
	int ret = lua_pcall(m_lua, 0, -1, 0);
	std::cout << "����ֵ��" << ret << std::endl;

	//�������
	if (ret != 0) // ʧ�ܷ��ط�0ֵ��ʧ�ܵĴ�����ջ�������ַ�������
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;
	}
	printStackSize("----lua_pcall");
}


// luaL_dofile
void example3()
{ 
	int ret = luaL_dofile(m_lua, "./ex3/ex3.lua");
	std::cout << "����ֵ: " << ret << std::endl;

	//�������
	if (ret != 0) // ʧ�ܷ��ط�0ֵ��ʧ�ܵĴ�����ջ�������ַ�������
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;
	}
	
}


// luaL_loadfile
void example4()
{
	int ret = luaL_loadfile(m_lua, "./ex3/ex3.lua");
	std::cout << "����ֵ: " << ret << std::endl;

	//�������
	if (ret != 0) // ʧ�ܷ��ط�0ֵ��ʧ�ܵĴ�����ջ�������ַ�������
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;
	}
	int pcall_ret = lua_pcall(m_lua, 0, -1, 0);
	if (pcall_ret != 0)
	{
		std::cout << "pcall error" << std::endl;
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;

	}
	printStackSize("ִ����ϣ�");
}

// get/set global
void example5()
{
	printStackSize("1");
	lua_pushstring(m_lua, "hello"); // ��ջ��ѹ��һ��ֵ
	printStackSize("2");
	lua_setglobal(m_lua, "xxx"); // ��ջ����ֵ����Ϊ�������ҵ���ջ����ֵ��������Ϊxxx
	printStackSize("3");
	int ret = luaL_dofile(m_lua, "./ex3/ex5.lua");
	std::cout << "����ֵ: " << ret << std::endl;

	//�������
	if (ret != 0) // ʧ�ܷ��ط�0ֵ��ʧ�ܵĴ�����ջ�������ַ�������
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;
	}


	ret =  lua_getglobal(m_lua, "data");
	std::cout << ret << std::endl;

	//������
	//if (ret == LUA_TNIL || LUA_TNONE) // ��ȫ�ֱ����ڵ�ʱ��
	if (ret <= 0) //��
	{
		printStackSize("������ȫ�ֱ���"); // ����Ѵ���ֵѹ���ջ
		lua_pop(m_lua, 1);
		return;
	}

}

// ��ȡ��������
void example6()
{
	printStackSize("1");
	lua_pushstring(m_lua, "hello"); // ��ջ��ѹ��һ��ֵ
	printStackSize("2");
	lua_setglobal(m_lua, "xxx"); // ��ջ����ֵ����Ϊ�������ҵ���ջ����ֵ��������Ϊxxx
	printStackSize("3");
	int ret = luaL_dofile(m_lua, "./ex3/ex5.lua");


	//�������
	if (ret != 0) // ʧ�ܷ��ط�0ֵ��ʧ�ܵĴ�����ջ�������ַ�������
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;
	}


	// ȫ�ֱ�����
#if 0
	ret = lua_getglobal(m_lua, "data");
	//std::cout << ret << std::endl;

	//������
	//if (ret == LUA_TNIL || LUA_TNONE) // ��ȫ�ֱ����ڵ�ʱ��
	if (ret <= 0) //��
	{
		printStackSize("������ȫ�ֱ���"); // ����Ѵ���ֵѹ���ջ
		lua_pop(m_lua, 1);
		return;
	}
	printStackSize("------");
	//std::cout << lua_tonumber(m_lua, -1) << std::endl; // һ����tonumber ����Ϊ������ȡС����Ҳ��ȡ������������ת����
	std::cout << lua_tostring(m_lua, -1) << std::endl; // tostring һ�㲻����������С������ȡ����
	printStackSize("------");
#endif

	// ����ȫ�ֱ���
	lua_pushstring(m_lua, "123.0");
	printStackSize("-------");
	std::cout << lua_tonumber(m_lua, -1) << std::endl;
	std::cout << lua_tointeger(m_lua, -1) << std::endl;
	printStackSize("------");


}


// �����ͼ��
void example7()
{
	printStackSize("1");
	lua_pushstring(m_lua, "hello"); // ��ջ��ѹ��һ��ֵ
	printStackSize("2");
	lua_setglobal(m_lua, "xxx"); // ��ջ����ֵ����Ϊ�������ҵ���ջ����ֵ��������Ϊxxx
	printStackSize("3");
	int ret = luaL_dofile(m_lua, "./ex3/ex5.lua");


	//�������
	if (ret != 0) // ʧ�ܷ��ط�0ֵ��ʧ�ܵĴ�����ջ�������ַ�������
	{
		const char* errostr = lua_tostring(m_lua, -1);
		std::cout << errostr << "\n";
		// �������Ҫ�����ֵ������
		lua_pop(m_lua, 1);// ����걾���ϻ���lua_settop()
		return;
	}


	// ȫ�ֱ�����
#if 1
	ret = lua_getglobal(m_lua, "data");
	//std::cout << ret << std::endl;

	//������
	//if (ret == LUA_TNIL || LUA_TNONE) // ��ȫ�ֱ����ڵ�ʱ��
	if (ret <= 0) //��
	{
		printStackSize("������ȫ�ֱ���"); // ����Ѵ���ֵѹ���ջ
		lua_pop(m_lua, 1);
		return;
	}

	printStackSize("------");
#endif


	std::cout << lua_isnumber(m_lua, -1) << std::endl;
	std::cout << lua_isinteger(m_lua, -1) << std::endl;
	printStackSize("------");

	printf("lua_type\n");
	std::cout << lua_type(m_lua, -1) << std::endl;
	std::cout << lua_typename(m_lua, lua_type(m_lua,-1)) << std::endl;



}

int main() {
	if (InitLua() == false)
	{
		return 0;
	}

	example7();

	return 0;
}