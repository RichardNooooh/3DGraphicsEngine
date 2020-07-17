#include <Windows.h>

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
	wc.lpfnWndProc = DefWindowProc;
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
	int rc;
	while ((rc = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return rc;
}