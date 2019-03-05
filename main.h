#include <iostream>
#include <algorithm>
#include <windows.h>
#include <cmath>
#include <string>

#include <vector>
using namespace std;

// 
struct xLine {
	
	xLine(int xStart, int xEnd, int yStart, int yEnd)
		: xStart (xStart), xEnd (xEnd), yStart (yStart), yEnd (yEnd), pen (NULL), nup (false) { };
	
	xLine(int xStart, int xEnd, int yStart, int yEnd, HPEN pen)
		: xStart (xStart), xEnd (xEnd), yStart (yStart), yEnd (yEnd), pen (pen), nup (false) { };
		
	xLine(int xStart, int xEnd, int yStart, int yEnd, bool nup)
		: xStart (xStart), xEnd (xEnd), yStart (yStart), yEnd (yEnd), pen (NULL), nup (nup) { };
	
	xLine(int xStart, int xEnd, int yStart, int yEnd, HPEN pen, bool nup)
		: xStart (xStart), xEnd (xEnd), yStart (yStart), yEnd (yEnd), pen (pen), nup (nup) { };
	
	int xStart;
	int xEnd;
	
	int yStart;
	int yEnd;
	
	bool nup;
	
	HPEN pen;

	COLORREF color;
};


struct xObj {
	xObj() : type (0) {};
	
	xObj(vector<xLine> lines)
		: lines (lines), type (0) { };

	xObj(vector<xLine> lines, int type)
		: lines (lines), type (type) { };


	vector<xLine> lines;
	
	int type;
	// int size;	
	// bool selected;
};



int updateDraw(HWND hWnd, RECT lprcUpdate);
vector<xLine> getFastXLines(int type, int pX, int pY);


