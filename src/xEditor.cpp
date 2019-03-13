#include "../stdafx.h"
#include "xEditor.h"


LRESULT CALLBACK xEditorWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	xEditor *ed = (xEditor*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	switch(Message) {
		
		case WM_NCCREATE: {
			ed = new xEditor(hWnd);
			if(ed) {
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ed);
			}
			else SendMessage(hWnd, WM_DESTROY, 0, 0);
				
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		
		case WM_NCDESTROY: {
			if(ed)
				delete ed;
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
	}
	return ed->event(hWnd, Message, wParam, lParam);
}

int xEditor::onCreate(CREATESTRUCT *cs) {
	
	scolorWnd = CreateWindowEx(WS_EX_TOOLWINDOW, xSColorClassName, "s Color", WS_OVERLAPPEDWINDOW|WS_HSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200, hWnd, NULL, NULL, NULL);
	//SetParent(hWnd, scolorWnd);
	//ShowWindow(scolorWnd, SW_SHOW);
	
	toolsWnd = CreateWindowEx(WS_EX_TOOLWINDOW, xToolsClassName, "Tools", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 100, 300, hWnd, NULL, NULL, NULL);
	//SetParent(toolsWnd, hWnd);
	//ShowWindow(toolsWnd, SW_SHOW);
	
	hdc = GetDC(hWnd);
	
	// Set bar menu
	xMenu menu;
	menu.set(hWnd);
	
	
	
	
	return 0;
}


int posX = 150,
	posY = 100,
	
	posXStart = 0,
	posYStart = 0,
	
	sizeR = 60,
	
	sizeObj = 1,
	
	curObjID = 2,
	modePen = 5;

int selectableObjID = 0;
bool mouseDown = false;

HPEN hOldPen, 
	hPen;

class MyPaint {
	public:
		myPaint();
		vector<xObj> drawObjs;
		xObj* previewObj;
};
MyPaint MPT;


int xEditor::onPaint() {
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	
	// SetStretchBltMode(hdc, COLORONCOLOR);
	
	// Draw ...
	
	GetClientRect(hWnd, &rect);
	
	rect.left = 10;
	// Draw obj name Text
	char objNameText[] = "Obj:",
	objLetterN[255];
	sprintf(objLetterN, "%s", (curObjID==0? "A": curObjID==1? "B": curObjID==2? "C": curObjID==3? "D": "OTHER"));
	
	sprintf(objNameText, "%s [%d] %s", objNameText, curObjID, objLetterN);
	
	rect.top = 10;
	DrawText(hDC, objNameText, -1, &rect, DT_LEFT | DT_TOP);
	// .
	
	// Draw size Text
	char sizeText[255];
	sprintf(sizeText, "Size: %d", sizeObj);
	
	rect.top += 20;
	DrawText(hDC, sizeText, -1, &rect, DT_LEFT | DT_TOP);
				// .
	
				// Draw selected obj ID Text
	char selectedObjText[255];
	sprintf(selectedObjText, "Selected ID: %d", selectableObjID);
	
	rect.top += 20;
	DrawText(hDC, selectedObjText, -1, &rect, DT_LEFT | DT_TOP);
				// .
	
				// Draw mode pen Text
	char modePenText[255], modePenName[255];
	sprintf(modePenName, "%s", (
		modePen==XPEN_POSITION? "Position":
		modePen==XPEN_SIZE? "Size":
		modePen==XPEN_COLOR? "Color":
		modePen==XPEN_CREATE? "Create":
		modePen==XPEN_ROTATION? "Rotation": "OTHER")
	);
	sprintf(modePenText, "Mode Pen: [%d] %s ", modePen, modePenName);
	
	rect.top += 25;
	DrawText(hDC, modePenText, -1, &rect, DT_LEFT | DT_TOP);
				// .
	
	
				// Draw ...
	char countObjsText[] = "Count obj:";
	sprintf(countObjsText, "%s %d", countObjsText, MPT.drawObjs.size());
	rect.top += 20;
	DrawText(hDC, countObjsText, -1, &rect, DT_LEFT | DT_TOP);
				// .
	
	rect.top = 0;
	
	
	
				// Установка координат к курсору
	MoveToEx(hDC, posX, posY, NULL);
	
	if(hPen == NULL) {
		hPen = CreatePen(PS_SOLID, 2, RGB(120, 120, 100));
	}
	
				//hOldPen = (HPEN) SelectObject(hDC, hPen);
	
				// Draw objects
	for(int doID=0; doID<MPT.drawObjs.size(); doID++) {	
		xObj curObj = MPT.drawObjs[doID];
					// ... set pen and other
		bool selected = (selectableObjID != 0 && doID == selectableObjID-1);
		
					// Draw object line
		for(int i=0; i<curObj.lines.size(); i++) {
			xLine p = curObj.lines[i];
			
			if(selected) {
				HPEN selPen = (HPEN) CreatePen(PS_SOLID, 3, RGB(240, 100, 80));
				hOldPen = (HPEN) SelectObject(hDC, selPen);
			}
			else if(p.pen != NULL) {
				hOldPen = (HPEN) SelectObject(hDC, p.pen);
			}
			
			if(!p.nup || i==0)				
				MoveToEx(hDC, p.xStart, p.yStart, NULL);
			LineTo(hDC, p.xEnd, p.yEnd);
			
			if(hOldPen) {
				SelectObject(hDC, hOldPen);
				hOldPen = NULL;
			}
			
			if(i==0) {					
				char ZZZZ[] = "";
				sprintf(ZZZZ, "%s%d", (selected? "S ": ""), curObj.type);
				rect.top = p.yStart;
				rect.left = p.xStart;
				DrawText(hDC, ZZZZ, -1, &rect, DT_LEFT | DT_TOP);
			}
		}
	}
	
	if(MPT.previewObj != NULL) {
		
					// Draw preview
		HPEN prevPen = CreatePen(PS_SOLID, 3, RGB(130, 150, 150));
		hOldPen = (HPEN) SelectObject(hDC, prevPen);
		
		for(int i=0; i<MPT.previewObj->lines.size(); i++) {
			xLine p = MPT.previewObj->lines[i];
			
			if(!p.nup || i==0)				
				MoveToEx(hDC, p.xStart, p.yStart, NULL);
			LineTo(hDC, p.xEnd, p.yEnd);
			
			if(i==0) {					
				char ZZZZ[] = "TYPE ID:";
				sprintf(ZZZZ, "%d", MPT.previewObj->type);
				rect.top = p.yStart;
				rect.left = p.xStart;
				DrawText(hDC, ZZZZ, -1, &rect, DT_LEFT | DT_TOP);
			}
		}
		
		if(hOldPen) {
			SelectObject(hDC, hOldPen);
			hOldPen = NULL;
		}
	}

	
	EndPaint(hWnd, &ps);
	return 0;
}
int xEditor::onDestroy() {
	menu.set(hWnd);
	
	ReleaseDC(hWnd, hdc);
	DestroyWindow(hWnd);
	DestroyWindow(scolorWnd);
	
	PostQuitMessage(0);
	return 0;
}

int xEditor::onCommand(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(wParam) {
		case MENU_EXIT: {
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		case MENU_COLORS: {
			ShowWindow(scolorWnd, SW_SHOW);
			break;
		}
		case MENU_TOOLS: {
			ShowWindow(toolsWnd, SW_SHOW);
			break;
		}
	}
	return 0;
}

int xEditor::onKeyDown(int key, int flag) {
	
	switch(key) {
		case VK_UP: {
			sizeObj = (sizeObj>=MAX_SIZE_OJB)? MAX_SIZE_OJB: ++sizeObj;
			updateDraw(hWnd, rect);
			break;
		}
		case VK_DOWN: {
			sizeObj = (sizeObj<=MIN_SIZE_OJB)? MIN_SIZE_OJB: --sizeObj;
			updateDraw(hWnd, rect);
			break;
		}
		
		case VK_LEFT: {
			selectableObjID = (selectableObjID <= 0)? 0: --selectableObjID;
			updateDraw(hWnd, rect);
			break;
		}
		case VK_RIGHT: {
			selectableObjID = (selectableObjID >= MPT.drawObjs.size())? MPT.drawObjs.size(): ++selectableObjID;
			updateDraw(hWnd, rect);
			break;
		}
		
		case VK_DELETE: {
			if(selectableObjID != 0) {
				MPT.drawObjs.erase(MPT.drawObjs.begin()+(selectableObjID-1));
				selectableObjID = (selectableObjID <= 0)? 0: --selectableObjID;
				updateDraw(hWnd, rect);
			}
			break;
		}
	}
}

int xEditor::onMouseWhell(short wheel_delta) {	
	if(wheel_delta > 0) {
		curObjID = (curObjID>=OBJ_COUNT)? OBJ_COUNT: ++curObjID;
	}
	else {
		curObjID = (curObjID==0)? 0: --curObjID;
	}
	updateDraw(hWnd, rect);
}

int xEditor::onLButtonDown(int x, int y, int keys) {
	mouseDown = true;

	if(keys & MK_SHIFT) {
	
		posXStart = x;
		posYStart = y;
		
		updateDraw(hWnd, rect);
	}
}

int xEditor::onLButtonUp(int pX, int pY, int keys) {
	if(MPT.previewObj != NULL || (mouseDown && modePen==XPEN_CREATE)) {
		MPT.previewObj = NULL;
		
		vector<xLine> p = getFastXLines(curObjID, pX, pY);
		
		for(int i=0; i<p.size(); ++i) {
			p[i].xStart += pX; p[i].xEnd += pX;
			p[i].yStart += pY; 	p[i].yEnd += pY;
		}
		
		xObj newObj(p, curObjID);
		
		MPT.drawObjs.push_back(newObj);
		
		updateDraw(hWnd, rect);
	}
	
	mouseDown = false;
}

int xEditor::onMouseMove(int pX, int pY, int keys) {
	// "Перемещение" (смена координат) при нажатой ЛКМ
	if(keys & MK_LBUTTON) {
		switch(modePen) {
			case XPEN_POSITION: {
				posX = pX;
				posY = pY;
				break;
			}
			case XPEN_ROTATION: {
				
				break;
			}
			case XPEN_COLOR: {
				hPen = CreatePen(PS_SOLID, 5, RGB(pX, pY+pX, pY));
				break;
			}
			case XPEN_CREATE: {
				vector<xLine> p = getFastXLines(curObjID, pX, pY);
	
				for(int i=0; i<p.size(); ++i) {
					p[i].xStart += pX; p[i].xEnd += pX;
					p[i].yStart += pY; p[i].yEnd += pY;
				}
	
				xObj newObj(p, curObjID);
	
				MPT.previewObj = &newObj;
	
				break;
			}
		}
	
		updateDraw(hWnd, rect);
	}
	
	if((keys | MK_LBUTTON) && MPT.previewObj != NULL) {
		MPT.previewObj = NULL;
	}
}



int updateDraw(HWND hWnd, RECT lprcUpdate) {
	GetClientRect(hWnd, &lprcUpdate);
	InvalidateRect(hWnd, &lprcUpdate, -1);
	
	UpdateWindow(hWnd);
}


vector<xLine> getFastXLines(int type, int pX, int pY) {
	
	vector<xLine> p;
	
	switch(type) {
		case 0: {
			p.push_back(xLine(0, sizeR, 0, sizeR));
			p.push_back(xLine(0, 0, 0, sizeR*2, true));
			p.push_back(xLine(0, -sizeR, 0, sizeR, true));
			p.push_back(xLine(0, 0, 0, 0, true));
			break;
		}
		
		case 1: {
			HPEN tPen = CreatePen(PS_SOLID, 20, RGB(255+pX, pX+pY, pY));
			// TOP
			p.push_back(xLine(0, -sizeR, 0, 0, tPen));
			p.push_back(xLine(0, +sizeR, 0, 0, tPen, true));
			
			// Bottom
			tPen = CreatePen(PS_SOLID, 10, RGB(pX, pX+255, pY+pX));
			p.push_back(xLine(0, +sizeR, 0, +sizeR, tPen, true));
			p.push_back(xLine(0, -sizeR, 0, +sizeR, tPen, true));
			
			// Side left up
			p.push_back(xLine(0, -sizeR, 0, 0, true));
			break;
		}
		case 2: {
			
			p.push_back(xLine(0, sizeR*cos(3.14/4), 0, sizeR*sin(3.14/6)));
			
			p.push_back(xLine(0, -sizeR, 0, sizeR, true));
			p.push_back(xLine(0, 0, 0, 0, true));
				
			break;
		}
		/*case 3: {
			HPEN tPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			const int mg = 50;
			for(int i=0; i<256;i++) {
				tPen = CreatePen(PS_SOLID, 1, RGB(255-i+pX, 128-i+pY, i));
			}
			break;
		}*/
		default: {
			p.push_back(xLine(0, 20, 20, 30));
			p.push_back(xLine(0, 60, 0, 10, true));
			break;
		}
	}
	
	return p;
}


