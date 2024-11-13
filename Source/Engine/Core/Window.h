#pragma once
#include "CascadeWin.h"

namespace cas
{
	class Window
	{
	public:
		Window(int width, int height, const char* name) noexcept;
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;

		Window& operator=(const Window&) = delete;
		Window& operator=(const Window&&) = delete;

	private:
		static LRESULT CALLBACK handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	private:
		int m_width;
		int m_height;
		HWND m_hwnd;
	private:
		class WindowClass
		{
		public:
			static const char* getName() noexcept;
			static HINSTANCE getInstance() noexcept;

			WindowClass(const WindowClass&) = delete;
			WindowClass(WindowClass&&) = delete;

			WindowClass& operator=(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&&) = delete;
		private:
			WindowClass() noexcept;
			~WindowClass();

			static constexpr const char* m_wndClassName = "Cascade Engine";
			static WindowClass m_wndClass;
			HINSTANCE m_hInstance;
		};
	};

}

