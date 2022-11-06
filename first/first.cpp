// ��Ϊc���Ժ�����c++�����ĺ������ڱ��뵽ϵͳ���ǲ�һ�µģ���������Ҫָ��һ��

// �����ʾ�ⲿ�ֺ���������c���Զ����
extern "C"
{
#include <lua.h> // ���Ӱ���Ŀ¼�������¾��У�windows�²����ִ�Сд
#include <lauxlib.h>
#include <lualib.h>
}


int CTest(lua_State* L) {
	printf("int CTest\n");
	size_t len;

	// lua��c++�����ַ���
	const char* name =  lua_tolstring(L, 1, &len); // �ڶ����ǣ�������ջ�е�λ�ã����������ַ�������
	printf("Lua name = %s\n", name);

	// lua��c++��������
	int age = lua_tonumber(L, 2);
	printf("Lua age = %d\n", age);

	// lua ��c++����bool
	bool is = lua_toboolean(L, 3);
	printf("Lua Is = %d\n", is);

	return 0;
}

// ����lua�е�����
int CTestArr(lua_State* L) {
	printf("In CTestArr\n");
	int len = luaL_len(L, 1);
	for (int i = 1; i <= len; i++)
	{
		lua_pushnumber(L, i); // ��lua��ֵ
		lua_gettable(L, 1); // pop index��Ȼ��push table[i]
		size_t size = 0;
		printf("%s\n", lua_tolstring(L, -1, &size)); // ��Ϊ�����table[i]ѹ����ջ��
		lua_pop(L, 1); // ���ƻ��ݣ�
	}
	return 0;
}

// ����lua ״̬ ����lua�ű�
int main() {
	// lua ״̬����һ��lua�Ķ�ջ�����º������еĳ����������ջ������
	//lua_State* lua = lua_open();//���������5.2���Ѿ������������µĺ���luaL_newstate��lua_newstate���,https://blog.csdn.net/x356982611/article/details/47405351
	lua_State* lua = luaL_newstate();

	//�򿪻�����
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);
	// ����ͨ��lua��ջ֪ͨlua��c++�ж���ĺ�����Ҳ����ͨ������õĺ���֪ͨ
	lua_register(lua, "CTest",CTest); //��һ��������lua��ջ���ڶ��������������ƣ�������������ָ��
	lua_register(lua, "CTestArr", CTestArr);


	//�����ļ�
	if (luaL_loadfile(lua, "main.lua"))
	{
		const char* error = lua_tostring(lua, -1);
		printf("lua load error:%s", error);
	}
	lua_pcall(lua, 0, 0, 0); // 2�Ժ��������������������ֵ��������

	getchar();
	return 0;
}