#include <iostream>
template <typename T>
T mget(); // һ�㲻��ȥʵ����,�������ػ���ʵ��
//T mget()
//{
//	std::cout << "T" << std::endl;
//}

// ģ���ػ�
template <>
int mget<int>() {
	std::cout << "int" << std::endl;
	return 111;
}
template <>
char* mget<char*>() {
	std::cout << "char*" << std::endl;
	return NULL;
}
template <>
void mget<void>() {
	std::cout << "void" << std::endl;
	return;
}



int main()
{
	mget<int>();
	mget<char*>();
	mget<void>();

	return 0;
}