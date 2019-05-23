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
		
	btnFig_1 = CreateWindowEx(0, "BUTTON", "Fig 1", WS_CHILD|WS_VISIBLE,
		0, 0,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_FIG_1, 0, NULL
	);
	btnFig_2 = CreateWindowEx(0, "BUTTON", "Fig 2", WS_CHILD|WS_VISIBLE,
		rect.right/2, 0,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_FIG_2, 0, NULL
	);
	
	btnFig_3 = CreateWindowEx(0, "BUTTON", "Fig 3", WS_CHILD|WS_VISIBLE,
		0, 32,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_FIG_3, 0, NULL
	);
	btnFig_4 = CreateWindowEx(0, "BUTTON", "Fig 4", WS_CHILD|WS_VISIBLE,
		rect.right/2, 32,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_FIG_4, 0, NULL
	);
	
	editPSize = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "1", WS_CHILD|WS_VISIBLE | ES_NUMBER,
		0, 64,
		rect.right, 30,
		hWnd, (HMENU) EDIT_PSIZE, 0, NULL);
	SendMessage(editPSize, EM_SETLIMITTEXT, 3, 0);
	
	btnCreate = CreateWindowEx(0, "BUTTON", "Create", WS_CHILD|WS_VISIBLE,
		0, 96,
		rect.right, 32,
		hWnd, (HMENU)BTN_CREATE, 0, NULL
	);
	
	btnPosition = CreateWindowEx(0, "BUTTON", "Pos", WS_CHILD|WS_VISIBLE,
		0, 128,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_POSITION, 0, NULL
	);
	btnRotate = CreateWindowEx(0, "BUTTON", "Rotate", WS_CHILD|WS_VISIBLE,
		rect.right/2, 128,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_ROTATE, 0, NULL
	);
	
	btnColor = CreateWindowEx(0, "BUTTON", "Color", WS_CHILD|WS_VISIBLE,
		0, 160,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_COLOR, 0, NULL
	);
	btnSize = CreateWindowEx(0, "BUTTON", "Size", WS_CHILD|WS_VISIBLE,
		rect.right/2, 160,
		rect.right/2, 32,
		hWnd, (HMENU) BTN_SIZE, 0, NULL
	);
	
	// ...
	return 0;
}

int xTools::onPaint() {
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	HBRUSH br1 = CreateSolidBrush(RGB(155, 200, 220));
	HBRUSH br2 = CreateSolidBrush(RGB(100, 230, 124));
	HBRUSH oldBr = (HBRUSH) SelectObject(hDC, br2);
	Rectangle(hDC, 30, 210, 70, 270);
	SelectObject(hDC, br1);
	Rectangle(hDC, 10, 200, 50, 250);
	HPEN oldPen = (HPEN) SelectObject(hDC, CreatePen(PS_SOLID, 2, 0));
	
	// ...
	
	DeleteObject(SelectObject(hDC, oldPen));
	SelectObject(hDC, oldBr);
	DeleteObject(br1);
	DeleteObject(br2);
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
	
	// Field Edit change value
	if(HIWORD(wParam) == EN_CHANGE) {
		switch(LOWORD(wParam)) {
			case EDIT_PSIZE: {		
				pSize = GetDlgItemInt( hWnd, EDIT_PSIZE, NULL, true);
				
				if(pSize <= 0) {
					pSize = 1;
					SetDlgItemInt(hWnd, EDIT_PSIZE, pSize, true);
				}
				SendMessage(hParentWnd, WM_COMMAND, CMD_SET_PSIZE, pSize);
				break;
			}
		}
	}
		
	switch(wParam) {
		case CMD_SET_PSIZE: {
			pSize = lParam;
			SetDlgItemInt(hWnd, EDIT_PSIZE, pSize, true);
			/*wchar_t buf[16];
			wsprintf((LPSTR)buf, "%d", pSize);
			SetWindowText(editPSize, (LPSTR)buf);*/
			return 0;
		}
	}
	
	if(HIWORD(wParam) == 0) {
		if(BTN_FIG_1 >= wParam && wParam <= BTN_FIG_4) SendMessage(lastBtnFigure, BM_SETSTATE, false, 0);
		if(wParam < BTN_CREATE) SendMessage(lastBtnMode, BM_SETSTATE, false, 0);
		
		switch(wParam) {
			case BTN_FIG_1: {
				SendMessage(hParentWnd, WM_COMMAND, CMD_SET_FIGURE, F_1);
				penMode = MODE_CREATE;
				break;
			}
			case BTN_FIG_2: {
				SendMessage(hParentWnd, WM_COMMAND, CMD_SET_FIGURE, F_2);
				penMode = MODE_CREATE;
				break;
			}
			case BTN_FIG_3: {
				SendMessage(hParentWnd, WM_COMMAND, CMD_SET_FIGURE, F_3);
				penMode = MODE_CREATE;
				break;
			}
			case BTN_FIG_4: {
				SendMessage(hParentWnd, WM_COMMAND, CMD_SET_FIGURE, F_4);
				penMode = MODE_CREATE;
				break;
			}
			case BTN_SIZE: {
				penMode = MODE_SIZE;
				break;
			}
			case BTN_ROTATE: {
				penMode = MODE_ROTATE;
				break;
			}
			/*case BTN_CERATE: {
				SendMessage(hParentWnd, WM_COMMAND, CMD_CREATE, 0);
				penMode = MODE_CREATE;
				break;
			}*/
			default: {
				penMode = MODE_POSITION;
				break;
			}
		}
		
		if(BTN_FIG_1 >= wParam && wParam <= BTN_FIG_4) {
			SendMessage((HWND) lParam, BM_SETSTATE, true, 0);
			lastBtnFigure = (HWND) lParam;
		}
		
		if(wParam < BTN_CREATE) {
			SendMessage((HWND) lParam, BM_SETSTATE, true, 0);
			lastBtnMode = (HWND) lParam;
		}
		
		SendMessage(hParentWnd, WM_COMMAND, CMD_SET_PEN, penMode);
		
		SetActiveWindow(hParentWnd);
	}
	
	return 0;
}

