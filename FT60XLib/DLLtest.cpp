#include "pch.h"
#include "DLLTest.h"
#include "iostream"

namespace DLLTest {
	HelloWorld::HelloWorld()
		: hoge(32)
	{
		std::cout << "HelloWorld " << hoge << std::endl;
	}

	void HelloWorld::HelloWorld::hello()
	{
		std::cout << "Hello";
		return;
	}

	void HelloWorld::HelloWorld::world()
	{
		std::cout << "World" << std::endl;
		return;
	}
}