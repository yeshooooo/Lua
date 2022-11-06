// 新建c库
// 此框架在linit.c 中插入
// 调试方法: 直接运行此程序,然后输入库名test为table,test.hello为函数类型.
// 调用test.hello()即可打印hello lua!!

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <stdio.h>
#include <stdio.h>
#include "md5.h"

// 添加static使得此函数只能在本文件中使用,规避重名
static int test_hello(lua_State* L)
{
	printf("hello lua!!\r\n");
	return 0; // return 的数值是返回的值的个数
}
static int test_fn1(lua_State* L)
{

	return 2; // 这里会从栈顶,依次返回n个lua脚本中传入的值
}
static int test_type_name(lua_State* L)
{
	int ltype = lua_type(L, 1);
	printf("lua type: %s\r\n", lua_typename(L, ltype));
	return 0; 
}
static int test_type_check(lua_State* L)
{
	int r = lua_isnumber(L, 1); // 是number类型的话返回1,不是的话返回0,在lua中不会返回错误信息
	if (r)
	{
		printf("是number!\n");
	}
	else
	{
		printf("不是number!\n");
	}
	luaL_checktype(L, 1,LUA_TNUMBER); // 类型不对的话在lua中会返回错误信息
	return 0;
}
// 获取lua中的数据,其他类型参见文档
// https://www.runoob.com/manual/lua53doc/contents.html
static int test_get_number(lua_State* L)
{
	int n = luaL_checkinteger(L, 1);
	printf("获取到了数据: %d\n", n);
	return 0;
}

static int test_get_string(lua_State* L)
{
	// 会有0x00截断的现象,数字也会转成字符串
	// 如 test.getString("asarfdafs"..string.char(0).."sadsafdafa")
	// > 获取到了字符串: asarfdafs
	char* s = luaL_checkstring(L, 1);

	//luaL_checklstring 可以获取字符串的长度,知道字符串里还有多少有效数据
	size_t len = 0;
	char* s1 = luaL_checklstring(L, 1, &len);

	printf("获取到了字符串: %s\n", s);
	printf("获取到了字符串: %lld\n", len);
	return 0;
}
//转换为目标类型并返回
static int test_get_bool(lua_State* L)
{
	int r = lua_toboolean(L, 1);
	if (r)
	{
		printf("是真\n");
	}
	else
	{
		printf("是假\n");
	}
	return 0;
}
static int test_get_opt_number(lua_State* L)
{
	int default1 = 10;
	int n = luaL_optinteger(L, 1, default1); // 如果lua传一个nil或者空过来,就会被设置成第三个参数,如10
	printf("获取到的数据:%d\n", n);
	return 0;
}

// ------------------------------c 压入栈
// 从c中向lua栈中推入数据
static int test_get_add_one(lua_State* L)
{
	int n = luaL_checkinteger(L, 1);
	lua_pushinteger(L, n + 1); // 将lua传过来的数据 + 1,并且压入到lua栈顶,返回多个值 return 相应的数字即可.
	return 1;
}

static int test_ret_string(lua_State* L)
{
	lua_pushstring(L, "abcdef");
	return 1;
}

// 复制栈中某个索引的参数的副本放入栈顶
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















// --------------------------------------------------------------注册库------------------------
// 结构体数组方法,当然也可以用内置方法注册,见动态库阶段笔记
// 这个结构体里面包含所有我们注册的接口
static const struct luaL_Reg testlib[] = {
	{"hello", test_hello}, // 注册c中的函数,第一个参数是函数的名字,第二个参数是在c里的函数名
	{"fn1", test_fn1},
	{"typeName", test_type_name},
	{"typeCheck", test_type_check},
	{"getNumber", test_get_number},
	{"getString", test_get_string},
	{"getBool", test_get_bool},
	{"getOptNumber", test_get_opt_number},

	// c向lua栈推入数据
	{"addOne", test_get_add_one},
	{"retString", test_ret_string},
	{"copy", test_copy},
	{"md5", test_md5},
	{NULL,NULL} // 最后一个数组的元素必须为这个

};

// 初始化用的函数
// 并把函数声明添加到lualib.h中
int luaopen_test(lua_State* L)
{
	luaL_newlib(L, testlib); // 注册testlib 数组

	return 1;
}
