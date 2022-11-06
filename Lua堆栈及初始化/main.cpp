#include "lua.hpp"


lua_State* L = NULL;
//��ʼ��lua����
void InitLua()
{
	L = luaL_newstate();
	if (L == NULL)
	{
		printf("error Lua��ʼ������ʧ��! �����쳣.....\n");
		return;
	}
	//����ȫ����
	luaL_openlibs(L);

	/*
	// �ֶ������ض���
	luaopen_base(L); //���ػ�����,�ȼ���
	luaopen_string(L);
	*/
}



//�ؼ�����
// 1. lua_pushstring ����һ���ַ�����Lua��ջ ,lua_tostring��ȡ��ջ�е��ַ���
// 2. lua_gettop ��ȡ��ջ�Ĵ�С
// 3. lua_settop ���ö�ջָ���λ��,��ָ��0,����ն�ջ.


// ���㸺���
int calc(int nindex, int nsize)
{
	return nindex - nsize - 1;
}



// ��ӡ��ǰ��ջ�Ĵ�С
// ���������ǩ��Ϊ�˿������ӡ�ķ���
// ���ұ���
void printStack(const char* tag)
{
	int sz = lua_gettop(L); //��ȡ��ջ��С
	printf("stacksize: %d <%s>\n", lua_gettop(L),tag);
	for (int i = 1; i <= sz; i++)
	{
		const char* str = lua_tostring(L, i);
		printf("index : %d , %d ----- %s \n", i, calc(i, sz),str);
	}

}




int main()
{
	InitLua();
	printStack("��ʼ�����");
	lua_pushfstring(L,"a");
	printStack("push a");

	//lua_settop(L, 0); //�����ջ

	lua_pushfstring(L, "b");
	printStack("push b");
	printf("----------------\n");
	lua_settop(L, 1);
	lua_pushstring(L, "c");
	printStack("push c");

	// ����Ӳ���lua_close����,������Ϊ�˴���淶,��Ϊ���̽������Զ��ͷ���Դ
	lua_close(L);
	L = nullptr;
	return 0;
}