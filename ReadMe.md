# lua c/c++ �����˱ʼ�
## 1 lualib ���뾲̬��
## 2 luadll ���붯̬��
1. ����LuaDll��������Ŀ����Ŀ¼��������Ӧ��̬��
2. ��Ϊfirst������References��Ե��,ֱ�ӱ���firstҲ����


# �̳�2
[�ο��̳�](https://edu.51cto.com/center/course/lesson/index?id=221460)
# 1 lua����
## 1.1 ����׼�����޸�Դ��
* lua�ṩ�˶��̷߳��ʵĻ�����������ֻ�����˺꣬��û��ʵ��
* �����ʱ����Ҫ����ƽ̨���޸ĺꡣwindowsƽ̨������ʹ���ٽ�����ʵ�֡�
	* ��ʼ���ٽ�����InitializeCriticalSection
    	* ��lstate.h ������ٽ����ṹ��
		* ��lstate,c �г�ʼ��
	* �����ٽ����� EnterCriticalSection
    	* ��llimits.h ��253���޸�
	* �뿪�ٽ����� LeaveCriticalSection
    	* ͬ��
	* Ȼ��close ��lstate.c ��

----
# Lua ��������
1. �ı��ջ��, ���Ķ�ջ��
2. ��L�ؼ���(��),����L�ؼ���
----
# luaִ�з�ʽ
## 1 ���ַ���ִ��
* luaL_dostring(L,�����ַ���)
    * ʧ�ܲŻ�ı��ջ,��ִ��(�ײ���luaL_loadstring() ��lua_pcall)
* luaL_loadstring(L,�����ַ���)
    * �����Ƿ�ʧ�ܶ���ı��ջ, ����ᱻ��װ��һ��������������ջ��,����ִ��
    * ����lua_pcall(L, ��������, ����ֵ����, ��������)
        * �Զ� ����ջ���ĺ���
![Lua Pcall](notepic/lua_pcall.png)
 

## 2 ��ȡ�ļ�ִ��  
    ͬ�ַ������������������ַ���������·����

* luaL_dofile()
* luaL_loadfile()
----
# ȫ�ֱ�������

## Cע��ȫ�ֱ���  
lua_setglobal(L, ȫ�ֱ�����)  
��ջ����ֵ����Ϊȫ�ֱ��������ҵ���ջ����ֵ  
    * lua���и�ȫ�ֱ� _G �洢��ȫ�ֱ��������Cע��ȫ�ֱ�����Ҳ����������в��ҵ���

## C��ȡluaȫ�ֱ���
#### lua_getglobal(L,ȫ�ֱ�����)  
��ȡlua�����е�ȫ�ֱ����������ջ  
����ֵ�� ȫ�ֱ���������  ����ֵ��Ӧ�����ֵĺ�����lua.h �У����� 3 ��number  
��ȫ�ֱ��������ڣ����� <= 0

#### lua_setglobal(L,ȫ�ֱ�����)
��ջ����ֵ����Ϊȫ�ֱ��������ҵ���ջ����ֵ

----
# �����������ͽ���
lua_tonumber,lua_tostring���ֲ���ı��ջ
![�����������ͽ���](notepic/�����������ͽ���.png)
![��������ת����](notepic/��������ת����.png)
С����ȡ�ַ�������������  
�ַ�����ȡ������С��
С����ȡ��������������ȡС��


----
# luaL_tolstring
![Lua L Tolstring](notepic/luaL_tolstring.png)
����һ��lua_tolstring() ����������ᴥ��Ԫ���"_tostring"����

----
# C++����Lua����������ע������ lua_pcall
lua_pcall�Ĳ���Ӱ���ջ,�Լ��Ƿ���ȷ����,��Ҫע��!
![Lua Pcall2](notepic/lua_pcall2.png)

----

## C++ ����Lua����-�䳤����ģ��ͷ���ֵ
* �䳤����ģ��  
  ����ֻд��c++11 �ݹ鷽��,δ����c++ 17 �۵����ʽ ��c++ 20������
```cpp
template<typename..._Args>
Function(_Args&...args)
{
}
```

![Temp Multi](notepic/temp_multi.png)
��֪ջ��-1��Ҫ��ȡĩβ��N��������
���ΧŹ-1-��N+1)

----
# TODO
[luaǶ��c++�̳�](https://www.youtube.com/watch?v=xrLQ0OXfjaI&list=PLLwK93hM93Z3nhfJyRRWGRXHaXgNX0Itk)
