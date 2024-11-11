#include <Windows.h>


int CALLBACK WinMain
(
		HINSTANCE hinstance,
		HINSTANCE /*hPrevInstance*/,
		LPSTR	/*lpCmdLine*/,
		int /*nCmdShow*/)
{
	//register window class
	constexpr auto className = "Cascade Engine";
	
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hinstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszClassName = className;
	RegisterClassEx(&wc);
	
	//create window instance
	HWND hWnd = CreateWindowEx(
		0,className,className,WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		200,200,640,480,nullptr,nullptr,hinstance,nullptr);

	//Show the window
	ShowWindow(hWnd,SW_SHOW);
	
	while (true)
	{
		
	}
	return 0;
}
