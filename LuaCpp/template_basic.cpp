#include <iostream>
template <typename T>
T mget(); // 一般不会去实现他,而是在特化中实现
//T mget()
//{
//	std::cout << "T" << std::endl;
//}

// 模板特化
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