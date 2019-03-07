#include "../stdafx.h"
#include "xTools.h"


LRESULT CALLBACK xToolsWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	xTools *t = (xTools*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	switch(Message) {
		
		case WM_NCCREATE: {
			t = new xTools(hWnd);
			if(t) {
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)t);
			}
			else SendMessage(hWnd, WM_DESTROY, 0, 0);
				
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		
		case WM_NCDESTROY: {
			if(t)
				delete t;
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
	}
	return t->event(hWnd, Message, wParam, lParam);
}

int xTools::onCreate(CREATESTRUCT *cs) {
	
	GetClientRect(hWnd, &rect);
	
	btnZZZ = CreateWindowEx(0, "BUTTON", "zzz", WS_CHILD|WS_VISIBLE, 0, 0, rect.right/2, 0, hWnd, (HMENU)BTN_ZZZ, 0, NULL);
	
	// ...
	return 0;
}

int xTools::onPaint() {
	PAINTSTRUCT ps;
	HDC uDC = BeginPaint(hWnd, &ps);
	
	
	
	EndPaint(hWnd, &ps);
	return 0;
}
int xTools::onDestroy() {
	
	
	return 0;
}
int xTools::onClose() {
	ShowWindow(hWnd, SW_HIDE);
	return 0;
}

int xTools::onCommand(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(wParam) {
		
	}
	return 0;
}

