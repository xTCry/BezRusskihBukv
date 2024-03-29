#include "../stdafx.h"
#include "xSColor.h"


LRESULT CALLBACK xSColorWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	xSColor *sc = (xSColor*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	switch(Message) {
		
		case WM_NCCREATE: {
			sc = new xSColor(hWnd);
			if(sc) {
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)sc);
			}
			else SendMessage(hWnd, WM_DESTROY, 0, 0);
				
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		
		case WM_NCDESTROY: {
			if(sc)
				delete sc;
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
	}
	return sc->event(hWnd, Message, wParam, lParam);
}

int xSColor::onCreate(CREATESTRUCT *cs) {
	
	hdc = GetDC(hWnd);
	SetScrollPos(hWnd, SB_HORZ, 100, true);
	
    char buf[50];
    sprintf(buf, "[xSColor::onCreate] [cs->lpCreateParams]: %d", cs->lpCreateParams);
	//MessageBox(NULL, buf, "Debug", MB_ICONASTERISK|MB_OK);
	
	if(cs->lpCreateParams == 0) {
		
		int wh = 500,
			hg = 500;
		
		BITMAPINFO bmi = { { sizeof(BITMAPINFOHEADER), wh, hg, 1, 32, BI_RGB } };
		
		hbm = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pBts, NULL, 0);
		hMemDC = CreateCompatibleDC(hdc);
		hbmOld = (HBITMAP) SelectObject(hMemDC, hbm);
	
		
		for(int i=0; i<wh; i++)
			for(int j=0; j<hg; j++)
				SetPixel(hMemDC, i, j, RGB(i, j+i, j));
		
	}
	
	return 0;
}

int xSColor::onPaint() {
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);
	
	GetClientRect(hWnd, &rect);
	
	BITMAP bmInfo;
	
	GetObject(hbm, sizeof(bmInfo), &bmInfo);
	
	SetStretchBltMode(hdc, HALFTONE);
	
	StretchBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);
	
	
	
	EndPaint(hWnd, &ps);
	
	return 0;
}
int xSColor::onDestroy() {
	SelectObject(hMemDC, hbmOld);
	DeleteObject(hbm);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	
	return 0;
}
int xSColor::onClose() {
	ShowWindow(hWnd, SW_HIDE);	
	return 0;
}

int xSColor::onCommand(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(wParam) {
		
	}
}
