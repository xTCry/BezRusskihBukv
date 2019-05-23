#pragma once

#include "../stdafx.h"
#include "xEvents.h"

#define CMD_SET_PSIZE 1020
#define CMD_SET_FIGURE 1021
#define CMD_SET_PEN 1022


#define BTN_POSITION 15
#define BTN_ROTATE 16
#define BTN_COLOR 17
#define BTN_SIZE 17

#define BTN_CREATE 20


// ..
#define BTN_FIG_1 311
#define BTN_FIG_2 312
#define BTN_FIG_3 313
#define BTN_FIG_4 314



#define EDIT_PSIZE 201

enum PenModes {
	MODE_COLOR = 0,
	MODE_SIZE = 1,
	MODE_POSITION,
	MODE_ROTATE,
	MODE_CREATE,
};
enum Figures {
	F_1 = 1,
	F_2 = 2,
	F_3 = 3,
	F_4 = 4,
};


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
		
		HWND lastBtnMode;
		HWND lastBtnFigure;
		
		HWND btnCreate;
		HWND btnFig_1;
		HWND btnFig_2;
		HWND btnFig_3;
		HWND btnFig_4;
		HWND btnPosition;
		HWND btnRotate;
		HWND btnColor;
		HWND btnSize;
		
		HWND editPSize;
		
		// Staff
		int pSize;
		int penMode;
};

