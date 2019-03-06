#ifndef XSCOLOR_H_INC
#define XSCOLOR_H_INC

#include "../stdafx.h"
#include "xEvents.h"


extern LRESULT CALLBACK DefaultWndProc(HWND, UINT, WPARAM, LPARAM);
class xSColor: public xEvents {
	public:
		xSColor(HWND _hWnd) {
			hWnd = _hWnd;
			hParentWnd = GetWindow(hWnd, GW_OWNER);
			if(hParentWnd == 0) DestroyWindow(hWnd);
		}
		
		int onCreate(CREATESTRUCT* ct) override;
		int onDestroy() override;
		int onClose() override;
		int onPaint() override;
		int onCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) override;
		
	private:
		HWND hWnd,
			hParentWnd;
		RECT rect;
		
		HDC hdc, hMemDC;
		
		BYTE *pBts;
		HBITMAP hbm, hbmOld;
};

#endif
