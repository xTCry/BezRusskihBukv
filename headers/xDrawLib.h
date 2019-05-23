#pragma once

#include "../stdafx.h"

class xDrawLib {
	public:
		virtual void Draw(HDC) =0;
};

class XT_Fig_1: public xDrawLib {
	xCoord coords;
	
	public:
		XT_Fig_1(POINT p1, POINT p2) : coords(xCoord(p1, p2)) { }
		
		void Draw(HDC hDC) {
			DeleteObject(SelectObject(hDC, CreatePen(PS_SOLID, 2, RGB(130, 150, 150))));
			MoveToEx(hDC, coords.xStart, coords.yStart, 0);
			LineTo(hDC, coords.xEnd, coords.yEnd);
		}
};


// 
struct xLine: xCoord {
	
	xLine()
		: xCoord (0, 0, 0, 0), pen (NULL), nup (false) { };
		
	xLine(int xStart, int xEnd, int yStart, int yEnd)
		: xCoord (xStart, xEnd, yStart, yEnd), pen (NULL), nup (true) { };
	
	xLine(int xStart, int xEnd, int yStart, int yEnd, HPEN pen)
		: xCoord (xStart, xEnd, yStart, yEnd), pen (pen), nup (true) { };
		
	xLine(int xStart, int xEnd, int yStart, int yEnd, bool nup)
		: xCoord (xStart, xEnd, yStart, yEnd), pen (NULL), nup (nup) { };
	
	xLine(int xStart, int xEnd, int yStart, int yEnd, HPEN pen, bool nup)
		: xCoord (xStart, xEnd, yStart, yEnd), pen (pen), nup (nup) { };
		
	bool nup;
	
	HPEN pen;

	COLORREF color;
};


struct xObj {
	xObj() : type (0) {};
	
	xObj(POINT pos, vector<xLine> lines, int size)
		: pos (pos), lines (lines), size (size), type (0), rotation ({ 0, 0 }) { };

	xObj(POINT pos, vector<xLine> lines, int size, int type)
		: pos (pos), lines (lines), size (size), type (type), rotation ({ 0, 0 }) { };

	POINT pos;
	vector<xLine> lines;
	
	int type;
	int size;
	POINT rotation;
	// bool selected;
};

