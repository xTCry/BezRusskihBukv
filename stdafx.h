#pragma once

#ifndef CCX_XX
#define CCX_XX

#include <windows.h>

#include <iostream>
#include <algorithm>

#include <cmath>
#include <string>
#include <vector>
#include <list>

#define PI 3.14159


using namespace std;

void cc(LPCSTR msg);


struct xCoord {
	
	xCoord(int xStart, int xEnd, int yStart, int yEnd)
		: xStart (xStart), xEnd (xEnd), yStart (yStart), yEnd (yEnd) { };
		
	xCoord(POINT p1, POINT p2)
		: xStart (p1.x), xEnd (p2.x), yStart (p1.y), yEnd (p2.y) { };
		
	int xStart;
	int xEnd;
	
	int yStart;
	int yEnd;
	
};

/*HBITMAP create32DIB(HDC hDC, int wh, int hg, BYTE **data) {
	BITMAPINFO BI;
	ZeroMemory(&BI, sizeof(BI));
	BI.bmiHeader.biSize = sizeof(BI);
	BI.bmiHeader.biWidth = wh;
	BI.bmiHeader.biHeight = - hg;
	BI.bmiHeader.biPlanes = 1;
	BI.bmiHeader.biBitCount = 32;
	BI.bmiHeader.biCompression = BI_RGB;
	
	return CreateDIBSection(hDC, &BI, DIB_RGB_COLORS, (VOID**)data, NULL, 0);
}*/

#endif

