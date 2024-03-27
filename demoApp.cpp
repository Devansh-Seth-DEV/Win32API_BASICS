#include <windows.h>
#include <wchar.h>

#define GENERATE_STR 1

struct ctrlPlot {
	UINT32 x, y;
	UINT32 nWidth, nHeight;
};

// -- functions prototype --
LRESULT CALLBACK fnWndProc(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);

// -- global variables --
int wndX = CW_USEDEFAULT;
int wndY = CW_USEDEFAULT;
int wndWidth = 500;
int wndHeight = 500;
PCWSTR wndClassName = L"dempAppClass";
HWND hEditName, hEditAge, hEditStr;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdShow) {
	WNDCLASSW wc = {0};

	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = wndClassName;
	wc.lpfnWndProc = &fnWndProc;

	
	if (!RegisterClassW(&wc)) {
		return -1;
	}	

	HWND hWnd = CreateWindowW(
			wndClassName, 													// Registered window class
			L"Demo Application",											// Window class text
			WS_VISIBLE | WS_OVERLAPPEDWINDOW,								// Window style
			wndX, wndY, wndWidth, wndHeight,								// Window position and size
			NULL, 															// Parent window
			NULL,															// Menu
			hInst,															// Instance handler
			NULL															// Additional app information
			);

	if (hWnd == NULL) {
		return 0;
	}

	MSG msg = {0};

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK fnWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch(msg)
	{
		case WM_CREATE:
			AddControls(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
			switch(wp)
			{
				wchar_t name[100], age[5], out[200];

				case GENERATE_STR:
					GetWindowTextW(hEditName, name, 100);
					GetWindowTextW(hEditAge, age, 5);

					wcscpy(out, name);
					wcscat(out, L" is ");
					wcscat(out, age);
					wcscat(out, L" years old.");

					SetWindowTextW(hEditStr, out);

					MessageBeep(MB_OK);
					break;
			}
			break;
	}

	return DefWindowProcW(hWnd, msg, wp, lp);
}

void AddControls(HWND hWnd) {
	struct ctrlPlot ssName, ssAge;
	struct ctrlPlot esName, esAge;
	struct ctrlPlot bGen;
	struct ctrlPlot esStr;

	// ploting the static and edit control
	ssName.nWidth = 100;
	ssName.nHeight = 40;
	ssName.x = (wndWidth-ssName.nWidth)>>2;
	ssName.y = 50;

	ssAge.nWidth = ssName.nWidth;
	ssAge.nHeight = ssName.nHeight;
	ssAge.x = ssName.x;
	ssAge.y = ssName.y + ssName.nHeight + 10;

	esName.nWidth = ssName.nWidth<<1;
	esName.nHeight = ssName.nHeight;
	esName.x = ssName.x + ssName.nWidth + 10;
	esName.y = ssName.y;

	esAge.nWidth = ssAge.nWidth;
	esAge.nHeight = ssAge.nHeight;
	esAge.x = esName.x;
	esAge.y = ssAge.y;

	// ploting button control
	bGen.nWidth = 100;
	bGen.nHeight = 30;
	bGen.x = ssName.x + ssName.nWidth;
	bGen.y = ssAge.y + ssAge.nHeight + 50;
	

	// edit control of message string
	esStr.nWidth = wndWidth-200;
	esStr.nHeight = ssName.nHeight<<1;
	esStr.x = (wndWidth-esStr.nWidth)>>1;
	esStr.y = bGen.y + bGen.nHeight + 50;
	
	// creating static control Name and Age
	CreateWindowW(L"static", L"Enter your name:", WS_VISIBLE | WS_CHILD,
			ssName.x, ssName.y, ssName.nWidth, ssName.nHeight,
			hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Enter your age:", WS_VISIBLE | WS_CHILD,
			ssAge.x, ssAge.y, ssAge.nWidth, ssAge.nHeight,
			hWnd, NULL, NULL, NULL);

	// creating edit control Name and Age
	hEditName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
			esName.x, esName.y, esName.nWidth, esName.nHeight,
			hWnd, NULL, NULL, NULL);

	hEditAge = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
			esAge.x, esAge.y, esAge.nWidth, esAge.nHeight,
			hWnd, NULL, NULL, NULL);

	// creating button contrl for generation of string
	CreateWindowW(L"button", L"Generate", WS_VISIBLE | WS_CHILD,
			bGen.x, bGen.y, bGen.nWidth, bGen.nHeight,
			hWnd, (HMENU) GENERATE_STR, NULL, NULL);

	// creating edit control for message string
	hEditStr = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
			esStr.x, esStr.y, esStr.nWidth, esStr.nHeight,
			hWnd, NULL, NULL, NULL);
}
