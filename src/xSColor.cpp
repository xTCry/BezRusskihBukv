#include "../stdafx.h"
#include "xSColor.h"


LRESULT CALLBACK xSColorWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	xSColor *sc = (xSColor*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
	
	switch(Message) {
		
		case WM_NCCREATE: {
			sc = new xSColor(hwnd);
			if(sc) {
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)sc);
			}
			else SendMessage(hwnd, WM_DESTROY, 0, 0);
				
			return DefWindowProc(hwnd, Message, wParam, lParam);
			break;
		}
		
		case WM_NCDESTROY: {
			if(sc)
				delete sc;
			return DefWindowProc(hwnd, Message, wParam, lParam);
			break;
		}
	}
	return sc->event(hwnd, Message, wParam, lParam);
}

int xSColor::onCreate(CREATESTRUCT *cs) {
	
	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(100, 110, 140)));
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.lpszClassName = "TT";
	wc.lpfnWndProc = DefaultWndProc;
			
	RegisterClass(&wc);
	HWND child = CreateWindowEx(0, "TT", NULL, WS_CHILD|WS_VISIBLE, 50, 60, 40, 50, hWnd, NULL, NULL, NULL);
			
	ShowWindow(child, SW_NORMAL);
	UpdateWindow(child);
	
	return 0x0EBA1;
}


int xSColor::onPaint() {
	
	return 0x0EBA1;
}
int xSColor::onDestroy() {
	
	return 0x0EBA1;
}

int xSColor::onCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(wParam) {
		
	}
}
