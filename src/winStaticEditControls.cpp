#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4

LRESULT CALLBACK WND_PROC(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND hEdit;

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
	

	// args: lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam
	CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
					NULL, NULL, NULL, NULL);

	MSG msg = {0};


	// msg loop it fetches the msgs, processes them and dispatches them to the window procedure to be processed further
	while( GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WND_PROC(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch(msg) {
		// this msg is passed only once when the window in created
		case WM_CREATE:
			AddMenus(hWnd);
			AddControls(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:

			switch(wp) {
				case FILE_MENU_EXIT:
					DestroyWindow(hWnd);
					break;
				
				case FILE_MENU_NEW:
					MessageBeep(MB_ICONINFORMATION);
					break;

				case CHANGE_TITLE:
					wchar_t text[100];
					GetWindowTextW(hEdit, text, 100);
					SetWindowTextW(hWnd, text);
					MessageBeep(MB_OK);
					break;
			}

			break;
	}

	return DefWindowProcW(hWnd, msg, wp, lp);
}

void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();

	HMENU hFileMenu = CreateMenu(); // popup menu for File Menu
	HMENU hSubMenu = CreateMenu(); // sub popup menu for Open SubMenu

	// Items for Sub Menu of File Menu
	AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, "Change Title");

	// Items for File Menu
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR) hSubMenu, "Open SubMenu");

	// Adding seperator: last two args can be ignored if it is a seperator
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	// Items for Window Menu
	// the identity 1 is passed to WPARAM wp of WND_PROC
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");

	// hMenu is added to hWnd window
	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
	// class name is not case sensitive for both static and edit control
  // SS_CENTER: static style text alignment to center
	CreateWindowW(L"static", L"Enter new window title here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 100, 50,
          hWnd, NULL, NULL, NULL);

  // ES_MULTILINE: edit style text to multiline
  // ES_AUTO[H/V]SCROLL: edit style text to scroll horizontally(AUTOHSCROLL) and vertically(AUTOVSCROLL)
	hEdit = CreateWindowW(L"edit", L"New Title", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 200, 152, 100, 50, 
          hWnd, NULL, NULL, NULL);
}
