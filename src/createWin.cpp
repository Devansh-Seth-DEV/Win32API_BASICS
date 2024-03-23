#include <windows.h>

LRESULT CALLBACK WND_PROC(HWND, UINT, WPARAM, LPARAM);

// HINSTANCE : id of our application given by OS
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASSW wc = {0};

	// defines the background of the window
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	
	// if not defined the cursor will not be displayed inside the window
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass"; // basic identifier for our class

	// part of event handler system
	wc.lpfnWndProc = &WND_PROC;

	
	if (!RegisterClassW(&wc))
		return -1; // tells the registration of window gets failed
	

	// fnArgs: lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam
	CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
					NULL, NULL, NULL, NULL);

	MSG msg = {0};

	// msg loop it fetches the msgs, processes them and dispatches them to the window procedure to be processed further
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WND_PROC(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0); break;
		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
	}
}
