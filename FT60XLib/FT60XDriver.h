#pragma once

#ifdef FT60XLIB_EXPORTS
#define FT60XLIB_API __declspec(dllexport)
#else
#define FT60XLIB_API __declspec(dllimport)
#endif


// Define when linking with static library
// Undefine when linking with dynamic library
#//define FTD3XX_STATIC


// Include D3XX library
#include "..\FTD3XX\include\FTD3XX.h"

#ifdef FT60XLIB_EXPORTS
#pragma comment(lib, "..\\FTD3XX\\x64\\FTD3XX.lib")
#endif

//end D3XX Include

#include <string>
#include <array>

//必要かもしれない
#include <iostream>

#define BUFFER_SIZE (1024*128)

union QuadBytes {
	unsigned char mChar[4];
	uint32_t m32int;
};

//_FT_DEVICE_LIST_INFO_NODEと互換性があるclass。関数を定義するために継承。
class FT60XInfo : public _FT_DEVICE_LIST_INFO_NODE{
private:
public:
	bool isSuperSpeed() { return ( (Flags & FT_FLAGS_SUPERSPEED) ? true : false ); };
	bool isHighSpeed() { return ((Flags & FT_FLAGS_HISPEED) ? true : false); };
	bool isOpend() { return ((Flags & FT_FLAGS_OPENED) ? true : false); };
	std::string GetDescription() { return std::string(Description); };
	std::string GetSerialNo() { return std::string(SerialNumber); };
};

class FT60XDriver
{
private:
	FT_HANDLE mHandle;
	FT_60XCONFIGURATION mChipConfig;

public:
	FT60XLIB_API FT60XDriver() {};
	FT60XLIB_API ~FT60XDriver() {};

	FT60XLIB_API int GetNumOfConnections();

	FT60XLIB_API bool Connect();
	FT60XLIB_API bool Close();
	
	FT60XLIB_API bool Read(QuadBytes *pDataBuf, int pDataSize);
	FT60XLIB_API bool Write(QuadBytes *pDataBuf, int pDataSize);

};

