#ifndef MAIN_H_INC
#define MAIN_H_INC

LPCSTR xSColorClassName = "xSColor Class";
LPCSTR xEditorClassName = "xEditor Class";
LPCSTR DefaultClassName = "xEditor Class";

LRESULT CALLBACK xEditorWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK xSColorWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	if (Message == WM_DESTROY)
		return 0;
	return DefWindowProc(hwnd, Message, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

//HINSTANCE hINST;

#endif
