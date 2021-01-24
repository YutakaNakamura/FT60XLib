#pragma once

#ifdef FT60XLIB_EXPORTS
#define FT60XLIB_API __declspec(dllexport)
#else
#define FT60XLIB_API __declspec(dllimport)
#endif

namespace DLLTest {
	class HelloWorld {
	public:
		int huga;
		FT60XLIB_API HelloWorld();
		static FT60XLIB_API void hello();
		FT60XLIB_API void world();
	private:
		int hoge = 0;
	};
}