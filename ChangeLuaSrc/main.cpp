#include "lua.hpp"


lua_State* L;
int main()
{
	// ��c/c++��ʹ�õ���Lϵ�еĽӿڣ��ײ���Ȼ��lua_newstate,��Ϊ�����ǹ̶��ģ�����û��Ҫÿ�ζ�д
	L = luaL_newstate(); 
	luaL_openlibs(L);
	luaL_dostring(L, "print 'Hello Lua!'");

	//��llex.c �ʷ���������������֧�֣������Թ�
	//luaL_dostring(L, "local ���� = 1�� \n print(����)");
	return 0;
}