#pragma once

#include "../stdafx.h"
#include "xDrawLib.h"

using namespace std;

class xpBuffer {
	public:
		xpBuffer(HWND, int, int);
		void DrawFigure(xDrawLib *);
		void DrawPaintToRender() {
			SetStretchBltMode(renderDC, COLORONCOLOR);
			// hMemDC -> renderDC
			StretchBlt(renderDC, 0, 0, width, height, hMemDC, 0, 0, width, height, SRCCOPY);
		}
		void DrawFigures(HDC);
		void DrawFullPaint();
		
		RECT getDrawRect() {
			RECT r;
			r.left = x;
			r.top = y;
			r.right = drawRect.right;
			r.bottom = drawRect.bottom;
			return r;
		}
		
		// list<xDrawLib *> figures;
		vector<xDrawLib *> figures;
		
		vector<xObj> drawObjs;
		xObj* previewObj;
		
		int selectableObjID = 0;		
		
	private:
		
		int height,
			width;
		
		int x = 0,
			y = 0;
		
		RECT drawRect;
		
		
		HPEN hOldPen, 
			hPen;
		
		HWND hWnd;
		HDC hDC,
			renderDC, hMemDC;
		
		BYTE *memBytes,
			*rendererBytes;
		HBITMAP oldMem,
				oldRenderer;
};


