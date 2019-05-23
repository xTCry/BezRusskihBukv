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
	
	scolorWnd = CreateWindowEx(WS_EX_TOOLWINDOW, xSColorClassName, "s Color", WS_OVERLAPPEDWINDOW|WS_HSCROLL, CW_USEDEFAULT, CW_USEDEFAULT,
		200, 200,
		hWnd, NULL, NULL, NULL);
	//SetParent(hWnd, scolorWnd);
	//ShowWindow(scolorWnd, SW_SHOW);
	
	toolsWnd = CreateWindowEx(WS_EX_TOOLWINDOW, xToolsClassName, "Tools", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		100, 300,
		hWnd, NULL, NULL, NULL);
	//SetParent(toolsWnd, hWnd);
	ShowWindow(toolsWnd, SW_SHOW);
	
	hDC = GetDC(hWnd);
	
	// Set bar menu
	xMenu menu;
	menu.set(hWnd);
	
	xpBuff = new xpBuffer(hWnd, 600, 750);
	
	// Set 
	pSize = 20;
	
	// Send to Tools
	SendMessage(toolsWnd, WM_COMMAND, CMD_SET_PSIZE, pSize);
	
	return 0;
}


const int sizeR = 5;


int xEditor::onPaint() {
	PAINTSTRUCT ps;
	hDC = BeginPaint(hWnd, &ps);
	
	SetStretchBltMode(hDC, COLORONCOLOR);
	
	DrawPaint();
	
	EndPaint(hWnd, &ps);
	return 0;
		
	
	//GetClientRect(hWnd, &rect);
	
	// Draw ...
	{
		/*rect.left = 10;
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
		
		//rect.top = 0;
		//rect.left = 0;
		rect.top += 20;*/
	
	
		/*MoveToEx(hDC, 20, 40, NULL);
		
		if(hPen == NULL) {
			hPen = CreatePen(PS_SOLID, 2, RGB(120, 120, 100));
		}
		
		//hOldPen = (HPEN) SelectObject(hDC, hPen);
		
		// Draw objects
		for(int doID=0; doID<MPT.drawObjs.size(); doID++) {
		
			hMemDC = CreateCompatibleDC(hDC);
		
			xObj curObj = MPT.drawObjs[doID];
			// ... set pen and other
			bool selected = (selectableObjID != 0 && doID == selectableObjID-1);
			POINT pos = curObj.pos;
			int msize = curObj.size;	
			POINT rotation = curObj.rotation;	
			
			{
				/*char rotationLabelT[] = { };
				sprintf(rotationLabelT, "Rotation : %d, %d", rotation.x, rotation.y);
				DrawText(hDC, rotationLabelT, -1, &rect, DT_LEFT | DT_TOP);
			}
			
			{
				char ZZZZ[] = "";
				sprintf(ZZZZ, "%s%d", (selected? "S ": ""), curObj.type);
				rect.left = pos.x;
				rect.top = pos.y;
				DrawText(hDC, ZZZZ, -1, &rect, DT_LEFT | DT_TOP);*-/
						
				rect.left = 0;
				rect.top = 0;
			}
					
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
				
				// ...
				p.xStart *= msize; p.xEnd *= msize;
				p.yStart *= msize; p.yEnd *= msize;
				
				double TR = sqrt(pow(p.xEnd+p.xStart, 2) + pow(p.yEnd+p.yStart, 2)),
					angel = acos(p.xEnd / TR);
				
				
				p.xEnd *= cos(angel + PI*rotation.x/90);
				p.xStart *= cos(angel + PI*rotation.x/90);
				p.yEnd *= sin(angel + PI*rotation.y/90);
				p.yStart *= sin(angel + PI*rotation.y/90);
				
				p.xStart += pos.x; p.xEnd += pos.x;
				p.yStart += pos.y; p.yEnd += pos.y;
				
				
				if(!p.nup)				
					MoveToEx(hDC, p.xStart, p.yStart, NULL);
					
				LineTo(hDC, p.xEnd, p.yEnd);
				
				if(hOldPen) {
					SelectObject(hDC, hOldPen);
					hOldPen = NULL;
				}
				
				if(i == 0) {
					
				}
			}
			
			BitBlt(hDC, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);
			DeleteDC(hMemDC);
		}
		
		if(MPT.previewObj != NULL) {
			
			// Draw preview
			HPEN prevPen = CreatePen(PS_SOLID, 3, RGB(130, 150, 150));
			hOldPen = (HPEN) SelectObject(hDC, prevPen);
			POINT pos = MPT.previewObj->pos;
			int msize = MPT.previewObj->size;
			POINT rotation = MPT.previewObj->rotation;
			
			for(int i=0; i<MPT.previewObj->lines.size(); i++) {
				xLine p = MPT.previewObj->lines[i];
				
				// ...
				p.xStart *= msize; p.xEnd *= msize;
				p.yStart *= msize; p.yEnd *= msize;
				
				p.xStart += pos.x; p.xEnd += pos.x;
				p.yStart += pos.y; p.yEnd += pos.y;
				
				//p.xStart *= sin(rotation); p.xEnd *= sin(rotation);
				//p.yStart *= sin(rotation); p.yEnd *= sin(rotation);
				
				if(!p.nup)
					MoveToEx(hDC, p.xStart, p.yStart, NULL);
				LineTo(hDC, p.xEnd, p.yEnd);
				
				/*if(i==0) {					
					char ZZZZ[] = "TYPE ID:";
					sprintf(ZZZZ, "%d", MPT.previewObj->type);
					rect.left = pos.x;
					rect.top = pos.y;
					DrawText(hDC, ZZZZ, -1, &rect, DT_LEFT | DT_TOP);
				}*-/
			}
			
			if(hOldPen) {
				SelectObject(hDC, hOldPen);
				hOldPen = NULL;
			}
		}
	
		
		EndPaint(hWnd, &ps);
		return 0;
		*/
	}
}
int xEditor::onDestroy() {
	menu.set(hWnd);
	
	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);
	DestroyWindow(scolorWnd);
	
	PostQuitMessage(0);
	return 0;
}


void xEditor::DrawPaint() {
	RECT rect;
	
	// xpBuff->DrawPaintToRender();
	
	xpBuff->DrawFullPaint();
	
	/*rect = xpBuff->getDrawRect();
	HRGN hrgn = CreateRectRgn(rect.left, rect.top, rect.left + rect.right, rect.top + rect.bottom);
	SelectClipRgn(hDC, hrgn);*/
}


int xEditor::onCommand(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(wParam) {
		
		case CMD_SET_PSIZE: {
			pSize = lParam;
			break;
		}
		case CMD_SET_FIGURE: {
			figure = (Figures) lParam;
			break;
		}
		case CMD_SET_PEN: {
			penMode = (PenModes) lParam;
			break;
		}
		
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
			break;
		}
		case VK_DOWN: {
			break;
		}
		
		case VK_LEFT: {
			xpBuff->selectableObjID = (xpBuff->selectableObjID <= 0)? 0: --xpBuff->selectableObjID;
			updateDraw(hWnd, rect);
			break;
		}
		case VK_RIGHT: {
			xpBuff->selectableObjID = (xpBuff->selectableObjID >= xpBuff->drawObjs.size())? xpBuff->drawObjs.size(): ++xpBuff->selectableObjID;
			updateDraw(hWnd, rect);
			break;
		}
		
		
		case VK_F1: {
			penMode = MODE_CREATE;
			// SendMessage ...
			break;
		}
		case VK_F2: {
			penMode = MODE_ROTATE;
			// SendMessage ...
			break;
		}
		
		case VK_DELETE: {
			if(xpBuff->selectableObjID != 0) {
				xpBuff->drawObjs.erase(xpBuff->drawObjs.begin()+(xpBuff->selectableObjID-1));
				xpBuff->selectableObjID = (xpBuff->selectableObjID <= 0)? 0: --xpBuff->selectableObjID;
				updateDraw(hWnd, rect);
			}
			break;
		}
	}
}

int xEditor::onMouseWhell(short wheel_delta, int keys) {
	if(keys & MK_SHIFT) {
		/*if(wheel_delta > 0) {
			curObjID = (curObjID>=OBJ_COUNT)? OBJ_COUNT: ++curObjID;
		}
		else {
			curObjID = (curObjID==0)? 0: --curObjID;
		}*/
	}
	else {
		if(wheel_delta > 0)
			pSize++;
		else
			pSize--;

		if(pSize <= 0)
			pSize = 1;
			
		SendMessage(toolsWnd, WM_COMMAND, CMD_SET_PSIZE, pSize);
	}
	updateDraw(hWnd, rect);
}

int xEditor::onLButtonDown(int x, int y, int keys) {
	LMBHold = true;
	LMStartPos = (POINT) { x, y };
	
	// fore test
	XT_Fig_1 fac(LMStartPos, LMStartPos);
	xpBuff->DrawFigure(&fac);
	
	
	
	if(penMode == MODE_CREATE) {
		vector<xLine> p = getFastXLines(figure, x, y);
		
		if(xpBuff->previewObj == NULL) {
			xObj newObj(LMStartPos, p, pSize, figure);
			xpBuff->previewObj = &newObj;
		}
		else {
			xpBuff->previewObj->pos = LMStartPos;
			xpBuff->previewObj->size = pSize;
		}
	}
	
	SendMessage(hWnd, WM_PAINT, 0, 0);
}

int xEditor::onLButtonUp(int pX, int pY, int keys) {
	if(xpBuff->previewObj != NULL || (LMBHold && penMode == MODE_CREATE)) {
		xpBuff->previewObj = NULL;
		
		vector<xLine> p = getFastXLines(figure, pX, pY);
				
		POINT pos = { pX, pY };
		xObj newObj(pos, p, pSize, figure);
		xpBuff->drawObjs.push_back(newObj);
		
		updateDraw(hWnd, rect);
	}
	
	LMBHold = false;
}

int xEditor::onMouseMove(int pX, int pY, int keys) {
	LMPos = (POINT)  { pX, pY };
	// "Перемещение" (смена координат) при нажатой ЛКМ
	if(keys & MK_LBUTTON) {
		switch(penMode) {
			case MODE_POSITION: {
				
				if(xpBuff->selectableObjID != 0) {
					xObj& curObj = xpBuff->drawObjs[xpBuff->selectableObjID-1];
					curObj.pos = LMPos;
				}
				break;
			}
			case MODE_ROTATE: {
				if(xpBuff->selectableObjID != 0) {
					xObj& curObj = xpBuff->drawObjs[xpBuff->selectableObjID-1];
					curObj.rotation.x = intLERP2(0, 360, abs(LMStartPos.x-pX));
					curObj.rotation.y = intLERP2(0, 360, abs(LMStartPos.y-pY));
				}
				break;
			}
			case MODE_COLOR: {
				//hPen = CreatePen(PS_SOLID, 5, RGB(pX, pY+pX, pY));
				break;
			}
			case MODE_CREATE: {
				vector<xLine> p = getFastXLines(figure, pX, pY);
					
				POINT pos = { pX, pY };
				
				if(xpBuff->previewObj == NULL) {
					xObj newObj(pos, p, pSize, figure);
					xpBuff->previewObj = &newObj;
				}
				else {
					xpBuff->previewObj->pos = pos;
					xpBuff->previewObj->size = pSize;
				}
	
				break;
			}
		}
	
		updateDraw(hWnd, rect);
	}
	
	if((keys | MK_LBUTTON) && xpBuff->previewObj != NULL) {
		xpBuff->previewObj = NULL;
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
		
		// недотреугольник
		case 0: {
			p.push_back(xLine());
			p.push_back(xLine(0, sizeR, 0, sizeR));
			p.push_back(xLine(0, 0, 0, sizeR*2));
			p.push_back(xLine(0, -sizeR, 0, sizeR));
			p.push_back(xLine(0, 0, 0, 0));
			break;
		}
		
		// 
		case 1: {
			
			HPEN tPen = CreatePen(PS_SOLID, 20, RGB(255+pX, pX+pY, pY));
			// TOP
			p.push_back(xLine());
			p.push_back(xLine(0, -sizeR, 0, 0, tPen));
			p.push_back(xLine(0, +sizeR, 0, 0, tPen));
			
			tPen = CreatePen(PS_SOLID, 10, RGB(pX, pX+255, pY+pX));
			// Bottom
			p.push_back(xLine());
			p.push_back(xLine(0, +sizeR, 0, +sizeR, tPen));
			p.push_back(xLine(0, -sizeR, 0, +sizeR, tPen));
			
			// Side left up
			p.push_back(xLine(0, -sizeR, 0, 0));
			break;
		}
		case 2: {
			p.push_back(xLine());
			
			p.push_back(xLine(0, sizeR*cos(PI/3), 0, sizeR*sin(PI/6)));
			
			p.push_back(xLine(0, sizeR*cos(PI/3), 0, sizeR*sin(PI/4)));
			p.push_back(xLine(0, sizeR*cos(PI/2), 0, sizeR*sin(PI/3)));
			p.push_back(xLine(0, sizeR*cos(PI/4), 0, sizeR*sin(PI/4)));
			p.push_back(xLine(0, -sizeR*cos(PI/5), 0, sizeR*sin(PI/2)));
			
			p.push_back(xLine(0, 0, 0, 0));
			
			break;
		}
		
		case 3: {
			p.push_back(xLine());
			p.push_back(xLine(0, sizeR*cos(3.14/4), 0, sizeR*sin(3.14/6)));
			p.push_back(xLine(0, -sizeR, 0, sizeR));
			p.push_back(xLine(0, 0, 0, 0));
				
			break;
		}
		
		default: {
			p.push_back(xLine());
			p.push_back(xLine(0, sizeR*3, sizeR, sizeR*1.5));
			p.push_back(xLine(0, sizeR*3, 0, sizeR/2));
			break;
		}
	}
	
	return p;
}


int intLERP2(int min, int max, int t) {
	return t > max? (t-max*( 1 /*t%max*/ )): t;
}
