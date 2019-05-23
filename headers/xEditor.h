#pragma once

#include "../stdafx.h"
#include "xEvents.h"
#include "xMenu.h"
#include "xTools.h"
#include "xpBuffer.h"
#include "xDrawLib.h"

extern LPCSTR xSColorClassName;
extern LPCSTR xToolsClassName;
extern LRESULT CALLBACK DefaultWndProc(HWND, UINT, WPARAM, LPARAM);


class xEditor: public xEvents {
	public:
		xEditor(HWND hWnd): hWnd (hWnd) { };
		
		int onCreate(CREATESTRUCT* ct) override;
		int onDestroy() override;
		int onPaint() override;
		int onCommand(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) override;
		int onMouseWhell(short wheel_delta, int keys) override;
		int onKeyDown(int key, int flag) override;
		
		int onMouseMove(int x, int y, int keys) override;
		
		int onLButtonUp(int x, int y, int keys) override;
		int onLButtonDown(int x, int y, int keys) override;
		
		// ...
		
		void DrawPaint();
		
	private:
		xpBuffer *xpBuff;
		
		HWND hWnd;
		
		HDC hDC;
		
		RECT rect;
		
		HWND scolorWnd, toolsWnd;
		
		xMenu menu;
		
		// Зажата ЛКМ
		bool LMBHold = false;
		// Позиция зажатой ЛКМ
		POINT LMStartPos;
		// Позиция текущей ЛКМ
		POINT LMPos;
		
		
		// Staff
		int pSize;
		int penMode;
		Figures figure;
};



int intLERP2(int min, int max, int t);

int updateDraw(HWND hWnd, RECT lprcUpdate);
vector<xLine> getFastXLines(int type, int pX, int pY);

