#include "SGWindow.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg) 
	{
	case WM_CLOSE:
		PostQuitMessage(420);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//Modified from ChiliTomatoNoodle's C++ DirectX Tutorial: https://www.youtube.com/watch?v=nQTiSLiNyk4
int CALLBACK WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int nCmdShow)
{
	const LPCWSTR pClassName = L"Test";

	//register window class
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	//create and show window instance
	DWORD windowStyles = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
	HWND hWnd = CreateWindowEx(0, pClassName,
							   L"Test Window", windowStyles,
							   200, 200, 640, 480,
							   nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOW);
	
	//barebones "message pump"
	MSG msg;
	BOOL rc;
	while ((rc = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		//Draw on the client window for this "frame"
		//Calculate the fps
	}

	return rc == -1 ? -1 : msg.wParam;
}