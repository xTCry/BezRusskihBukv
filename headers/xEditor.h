#ifndef XEDITOR_H_INC
#define XEDITOR_H_INC

#include "../stdafx.h"
#include "xEvents.h"
#include "xMenu.h"

extern LPCSTR xSColorClassName;
extern LRESULT CALLBACK DefaultWndProc(HWND, UINT, WPARAM, LPARAM);


#define MAX_SIZE_OJB 20
#define MIN_SIZE_OJB 1

#define OBJ_COUNT 4

#define MAX_PEN_MODE 5
#define XPEN_COLOR 1
#define XPEN_SIZE 2
#define XPEN_POSITION 3
#define XPEN_ROTATION 4
#define XPEN_CREATE 5


class xEditor: public xEvents {
	public:
		xEditor(HWND hWnd): hWnd (hWnd) { };
		
		int onCreate(CREATESTRUCT* ct) override;
		int onDestroy() override;
		int onPaint() override;
		int onCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) override;
		
	private:
		HWND hWnd;
		
		HDC hdc;
		
		HWND scolorWnd;
		
		xMenu menu;

};







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




#endif
