#ifndef XTOOLS_H_INC
#define XTOOLS_H_INC

#include "../stdafx.h"
#include "xEvents.h"

#define BTN_ZZZ 1

extern LRESULT CALLBACK DefaultWndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK xToolsWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
class xTools: public xEvents {
	public:
		xTools(HWND hWnd) : hWnd (hWnd) {
			hParentWnd = GetWindow(hWnd, GW_OWNER);
			if(hParentWnd == 0) DestroyWindow(hWnd);
		}
		
		int onCreate(CREATESTRUCT* ct) override;
		int onDestroy() override;
		int onClose() override;
		int onPaint() override;
		int onCommand(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) override;
		
	private:
		HWND hWnd,
			hParentWnd;
		RECT rect;
		
		HBITMAP hbm;
		
		HWND btnZZZ;
};



#endif
