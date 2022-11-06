// �½�c��
// �˿����linit.c �в���
// ���Է���: ֱ�����д˳���,Ȼ���������testΪtable,test.helloΪ��������.
// ����test.hello()���ɴ�ӡhello lua!!

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <stdio.h>
#include <stdio.h>
#include "md5.h"

// ���staticʹ�ô˺���ֻ���ڱ��ļ���ʹ��,�������
static int test_hello(lua_State* L)
{
	printf("hello lua!!\r\n");
	return 0; // return ����ֵ�Ƿ��ص�ֵ�ĸ���
}
static int test_fn1(lua_State* L)
{

	return 2; // ������ջ��,���η���n��lua�ű��д����ֵ
}
static int test_type_name(lua_State* L)
{
	int ltype = lua_type(L, 1);
	printf("lua type: %s\r\n", lua_typename(L, ltype));
	return 0; 
}
static int test_type_check(lua_State* L)
{
	int r = lua_isnumber(L, 1); // ��number���͵Ļ�����1,���ǵĻ�����0,��lua�в��᷵�ش�����Ϣ
	if (r)
	{
		printf("��number!\n");
	}
	else
	{
		printf("����number!\n");
	}
	luaL_checktype(L, 1,LUA_TNUMBER); // ���Ͳ��ԵĻ���lua�л᷵�ش�����Ϣ
	return 0;
}
// ��ȡlua�е�����,�������Ͳμ��ĵ�
// https://www.runoob.com/manual/lua53doc/contents.html
static int test_get_number(lua_State* L)
{
	int n = luaL_checkinteger(L, 1);
	printf("��ȡ��������: %d\n", n);
	return 0;
}

static int test_get_string(lua_State* L)
{
	// ����0x00�ضϵ�����,����Ҳ��ת���ַ���
	// �� test.getString("asarfdafs"..string.char(0).."sadsafdafa")
	// > ��ȡ�����ַ���: asarfdafs
	char* s = luaL_checkstring(L, 1);

	//luaL_checklstring ���Ի�ȡ�ַ����ĳ���,֪���ַ����ﻹ�ж�����Ч����
	size_t len = 0;
	char* s1 = luaL_checklstring(L, 1, &len);

	printf("��ȡ�����ַ���: %s\n", s);
	printf("��ȡ�����ַ���: %lld\n", len);
	return 0;
}
//ת��ΪĿ�����Ͳ�����
static int test_get_bool(lua_State* L)
{
	int r = lua_toboolean(L, 1);
	if (r)
	{
		printf("����\n");
	}
	else
	{
		printf("�Ǽ�\n");
	}
	return 0;
}
static int test_get_opt_number(lua_State* L)
{
	int default1 = 10;
	int n = luaL_optinteger(L, 1, default1); // ���lua��һ��nil���߿չ���,�ͻᱻ���óɵ���������,��10
	printf("��ȡ��������:%d\n", n);
	return 0;
}

// ------------------------------c ѹ��ջ
// ��c����luaջ����������
static int test_get_add_one(lua_State* L)
{
	int n = luaL_checkinteger(L, 1);
	lua_pushinteger(L, n + 1); // ��lua������������ + 1,����ѹ�뵽luaջ��,���ض��ֵ return ��Ӧ�����ּ���.
	return 1;
}

static int test_ret_string(lua_State* L)
{
	lua_pushstring(L, "abcdef");
	return 1;
}

// ����ջ��ĳ�������Ĳ����ĸ�������ջ��
static int test_copy(lua_State* L) {
	lua_pushvalue(L, 1);
	return 2;
}

// ------------------------------------------MD5
/* demo:
#include <stdio.h>
#include "md5.h"

int main()
{
	char s[]="abc";

	unsigned char md5_bin[16]={0};
	MD5_CTX md5c;
	MD5Init(&md5c);
	MD5Update(&md5c,(unsigned char *)s ,strlen(s));
	MD5Final(&md5c,md5_bin);

	unsigned char md5_hex[33]={0};
	int i;
	for(i=0;i<16;i++)
		sprintf((char*)(md5_hex+i*2),"%02X",md5_bin[i]);
	printf("md5:%s\n",md5_hex);

	return 0;
}
*/

static int test_md5(lua_State* L) {
	
	size_t len = 0;
	
	char* s = luaL_checklstring(L, 1, &len);//
	unsigned char md5_bin[16] = { 0 };
	MD5_CTX md5c;
	MD5Init(&md5c);
	MD5Update(&md5c, (unsigned char*)s, len); //
	MD5Final(&md5c, md5_bin);

	unsigned char md5_hex[33] = { 0 };
	int i;
	for (i = 0; i < 16; i++)
		sprintf((char*)(md5_hex + i * 2), "%02X", md5_bin[i]);
	lua_pushstring(L, md5_hex);
	
	return 1;
}















// --------------------------------------------------------------ע���------------------------
// �ṹ�����鷽��,��ȻҲ���������÷���ע��,����̬��׶αʼ�
// ����ṹ�����������������ע��Ľӿ�
static const struct luaL_Reg testlib[] = {
	{"hello", test_hello}, // ע��c�еĺ���,��һ�������Ǻ���������,�ڶ�����������c��ĺ�����
	{"fn1", test_fn1},
	{"typeName", test_type_name},
	{"typeCheck", test_type_check},
	{"getNumber", test_get_number},
	{"getString", test_get_string},
	{"getBool", test_get_bool},
	{"getOptNumber", test_get_opt_number},

	// c��luaջ��������
	{"addOne", test_get_add_one},
	{"retString", test_ret_string},
	{"copy", test_copy},
	{"md5", test_md5},
	{NULL,NULL} // ���һ�������Ԫ�ر���Ϊ���

};

// ��ʼ���õĺ���
// ���Ѻ���������ӵ�lualib.h��
int luaopen_test(lua_State* L)
{
	luaL_newlib(L, testlib); // ע��testlib ����

	return 1;
}
