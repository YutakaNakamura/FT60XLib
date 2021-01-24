// FT60XLibDevelop.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "DLLtest.h"
#include "FT60XDriver.h"

int main()
{
	//DLL test
	DLLTest::HelloWorld hello;
	DLLTest::HelloWorld::hello();
	hello.world();

	//FT60X DLL
	FT60XDriver driver;

	driver.Connect();

	constexpr int datarate = 16384;
	std::array<QuadBytes, datarate> *data = new std::array<QuadBytes, datarate>();
	driver.Read( (QuadBytes*)data, sizeof(*data) );

	std::for_each(data->begin(), data->end(), [&](QuadBytes data) {
		std::cout << (int)data.m32int << std::endl;
	});

	delete data;

	driver.Close();

}