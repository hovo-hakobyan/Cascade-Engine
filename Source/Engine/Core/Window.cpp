#include "Window.h"

namespace cas
{
	Window::Window(int width, int height, const char* name) noexcept
	{
		//create window instance
		m_hwnd = CreateWindowEx(
			0, name, name, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, WindowClass::getInstance(), nullptr);

		//Show the window
		ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	}

	Window::~Window()
	{
		DestroyWindow(m_hwnd);
	}

	LRESULT CALLBACK Window::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		//we override some behavior
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_LBUTTONDOWN:
			const POINTS mousePos = MAKEPOINTS(lParam);
			break;
		}

		// the rest gets handled by default window procedure
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	Window::WindowClass Window::WindowClass::m_wndClass;

	Window::WindowClass::WindowClass() noexcept
		: m_hInstance(GetModuleHandle(nullptr))
	{
		WNDCLASSEX wc{};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = handleMsg;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = m_wndClassName;
		RegisterClassEx(&wc);
	}

	Window::WindowClass::~WindowClass()
	{
		UnregisterClass(m_wndClassName, getInstance());
	}


	const char* Window::WindowClass::getName() noexcept
	{
		return m_wndClassName;
	}

	HINSTANCE Window::WindowClass::getInstance() noexcept
	{
		return m_wndClass.m_hInstance;
	}
}
