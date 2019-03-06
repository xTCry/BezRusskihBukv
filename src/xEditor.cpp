#include "../stdafx.h"
#include "xEditor.h"


LRESULT CALLBACK xEditorWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	xEditor *ed = (xEditor*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
	
	switch(Message) {
		
		case WM_NCCREATE: {
			ed = new xEditor(hwnd);
			if(ed) {
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ed);
			}
			else SendMessage(hwnd, WM_DESTROY, 0, 0);
				
			return DefWindowProc(hwnd, Message, wParam, lParam);
			break;
		}
		
		case WM_NCDESTROY: {
			if(ed)
				delete ed;
			return DefWindowProc(hwnd, Message, wParam, lParam);
			break;
		}
	}
	return ed->event(hwnd, Message, wParam, lParam);
}

int xEditor::onCreate(CREATESTRUCT *cs) {
	
	scolorWnd = CreateWindowEx(WS_EX_TOOLWINDOW, xSColorClassName, "s Color", WS_OVERLAPPEDWINDOW|WS_HSCROLL, 100, 300, 200, 200, hWnd, NULL, NULL, NULL);
	ShowWindow(scolorWnd, SW_SHOW);
	
	hdc = GetDC(hWnd);
	
	// Set bar menu
	xMenu menu;
	menu.set(hWnd);
	
	
	
	
	/*WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(125, 180, 40)));
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.lpszClassName = "TT";
	wc.lpfnWndProc = DefaultWndProc;
			
	RegisterClass(&wc);
	HWND child = CreateWindowEx(0, "TT", NULL, WS_CHILD|WS_VISIBLE, 20, 30, 60, 60, hWnd, NULL, NULL, NULL);
			
	ShowWindow(child, SW_NORMAL);
	UpdateWindow(child);*/
	
	return 0;
}

int xEditor::onPaint() {
	PAINTSTRUCT ps;
	HDC uDC = BeginPaint(hWnd, &ps);
	
	SetStretchBltMode(hdc, COLORONCOLOR);
	
	// Draw ...
	
	EndPaint(hWnd, &ps);
	return 0;
}
int xEditor::onDestroy() {
	menu.set(hWnd);
	
	ReleaseDC(hWnd, hdc);
	DestroyWindow(hWnd);
	DestroyWindow(scolorWnd);
	
	PostQuitMessage(0);
	return 0;
}

int xEditor::onCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(wParam) {
		case MENU_EXIT: {
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
		case MENU_COLORS: {
			MessageBox(NULL, "[xEditor::onCommand] [MENU_COLORS] invoke", "Debug", MB_ICONASTERISK|MB_OK);
			ShowWindow(scolorWnd, SW_SHOW);
			break;
		}
	}
}

/*LRESULT CALLBACK xEditorWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
	switch(Message) {
		
		case WM_CREATE: {
			
			//MessageBox(NULL, "[xEditorWndProc] [WM_CREATE] Start", "Debug", MB_ICONASTERISK|MB_OK);
						
			WNDCLASS wc;
			memset(&wc, 0, sizeof(WNDCLASS));
			//wc.hInstance = hINST;
			wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(125, 180, 40)));
			wc.hCursor = LoadCursor(NULL, IDC_CROSS);
			wc.lpszClassName = "TT";
			wc.lpfnWndProc = DefaultWndProc;
			
			RegisterClass(&wc);
			HWND child = CreateWindowEx(0, "TT", NULL, WS_CHILD|WS_VISIBLE, 20, 30, 60, 60, hwnd, NULL, NULL, NULL);
			
			ShowWindow(child, SW_NORMAL);
			UpdateWindow(child);
			
			//MessageBox(NULL, "[xEditorWndProc] [WM_CREATE] End", "Debug", MB_ICONASTERISK|MB_OK);
			break;
		}
		
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}*/

