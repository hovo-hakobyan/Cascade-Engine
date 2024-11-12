#include <Windows.h>


//Processes the messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//we override some behavrior
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(wParam == 'F')
		{}
		break;
	case WM_CHAR: //Input that corresponds with text
		{}
		break;
	case WM_LBUTTONDOWN:
		const POINTS mousePos= MAKEPOINTS(lParam);
		break;
	}

	// the rest gets handled by default window procedure
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

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
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className;
	RegisterClassEx(&wc);
	
	//create window instance
	HWND hWnd = CreateWindowEx(
		0,className,className,WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		200,200,640,480,nullptr,nullptr,hinstance,nullptr);

	//Show the window
	ShowWindow(hWnd,SW_SHOW);
	
	MSG msg;
	BOOL result;
	while ( (result = GetMessage(&msg,nullptr,0,0)) >0)
	{
		TranslateMessage(&msg); //important for translating WM_CHAR
		DispatchMessage(&msg);
	}

	if(result == -1) return -1;
	return msg.wParam;
}
