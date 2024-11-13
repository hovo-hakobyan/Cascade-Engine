#include "Window.h"



int CALLBACK WinMain
(
		HINSTANCE,
		HINSTANCE,
		LPSTR,
		int )
{
	cas::Window wnd{ 1024,700,"Cascade Engine" };

	MSG msg;
	BOOL result;
	while ( (result = GetMessage(&msg,nullptr,0,0)) >0)
	{
		TranslateMessage(&msg); //important for translating WM_CHAR
		DispatchMessage(&msg);
	}

	if(result == -1) return -1;
	return static_cast<int>( msg.wParam);
}
