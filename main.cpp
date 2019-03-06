#include "stdafx.h"
#include "main.h"
#include "xEditor.h"
#include "xSColor.h"

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


/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//hINST = hInstance;
	
	int 
		sizeW = GetSystemMetrics(SM_CXSCREEN)/2,
		sizeH = GetSystemMetrics(SM_CYSCREEN)/2,
		wPosX = sizeW/2,
		wPosY = sizeH/2;
	
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	//wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(215, 220, 205)));
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
	
	
	// Reg xEditor Class
	wc.lpfnWndProc	 = xEditorWndProc; /* This is where we will send messages to */
	wc.lpszClassName = xEditorClassName;
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	// Reg xSColor Class
	wc.lpfnWndProc	 = xSColorWndProc; /* This is where we will send messages to */
	wc.lpszClassName = xSColorClassName;
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, xEditorClassName, "xTCry LOL Paint", WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		wPosX, /* x */
		wPosY, /* y */
		sizeW, /* width */
		sizeH, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}






/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	
	
	switch(Message) {
		
		case WM_CREATE: {
			break;
		}
		case WM_PAINT: {
			
			hDC = BeginPaint(hwnd, &ps);
			
			GetClientRect(hwnd, &rect);
			
			
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
		
			EndPaint(hwnd, &ps);		
			
			break;
		}
		
		case WM_KEYDOWN: {
			switch(wParam) {
				case VK_UP: {
					sizeObj = (sizeObj>=MAX_SIZE_OJB)? MAX_SIZE_OJB: ++sizeObj;
					updateDraw(hwnd, rect);
					break;
				}
				case VK_DOWN: {
					sizeObj = (sizeObj<=MIN_SIZE_OJB)? MIN_SIZE_OJB: --sizeObj;
					updateDraw(hwnd, rect);
					break;
				}
				
				case VK_LEFT: {
					selectableObjID = (selectableObjID <= 0)? 0: --selectableObjID;
					updateDraw(hwnd, rect);
					break;
				}
				case VK_RIGHT: {
					selectableObjID = (selectableObjID >= MPT.drawObjs.size())? MPT.drawObjs.size(): ++selectableObjID;
					updateDraw(hwnd, rect);
					break;
				}
				
				case VK_DELETE: {
					if(selectableObjID != 0) {
						MPT.drawObjs.erase(MPT.drawObjs.begin()+(selectableObjID-1));
						selectableObjID = (selectableObjID <= 0)? 0: --selectableObjID;
						updateDraw(hwnd, rect);
					}
					break;
				}
				
				/*case VK_CONTROL: {
					modePen = (modePen >= MAX_PEN_MODE)? 0: ++modePen;
					updateDraw(hwnd, rect);
					break;
				}*/
			}
			break;
		}
		
		case WM_MOUSEMOVE: {
			int pX = LOWORD(lParam),
				pY = HIWORD(lParam);
		
			// "Перемещение" (смена координат) при нажатой ЛКМ
			if(wParam & MK_LBUTTON) {
				switch(modePen) {
					case XPEN_POSITION: {
						posX = LOWORD(lParam);
						posY = HIWORD(lParam);
						break;
					}
					case XPEN_ROTATION: {
						// ...
						break;
					}
					case XPEN_COLOR: {
						hPen = CreatePen(PS_SOLID, 5, RGB(LOWORD(lParam), LOWORD(lParam)+HIWORD(lParam), HIWORD(lParam)));
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
				
				updateDraw(hwnd, rect);
			}
			if(wParam | MK_LBUTTON && MPT.previewObj != NULL) {
				MPT.previewObj = NULL;
			}
			break;
		}
		
		case WM_LBUTTONUP: {
			int pX = LOWORD(lParam),
				pY = HIWORD(lParam);
			
			if(MPT.previewObj != NULL || (mouseDown && modePen==XPEN_CREATE)) {
				MPT.previewObj = NULL;
				
				vector<xLine> p = getFastXLines(curObjID, pX, pY);
				
				for(int i=0; i<p.size(); ++i) {
					p[i].xStart += pX; p[i].xEnd += pX;
					p[i].yStart += pY; 	p[i].yEnd += pY;
				}
				
				xObj newObj(p, curObjID);
				
				MPT.drawObjs.push_back(newObj);
				
				updateDraw(hwnd, rect);
			}
			
			mouseDown = false;
			break;
		}
		
		case WM_LBUTTONDOWN: {
			mouseDown = true;
			// Клик ЛКМ и нажат Shift
			if(wParam & MK_SHIFT) {
				int pX = LOWORD(lParam),
					pY = HIWORD(lParam);
					
				posXStart = pX;
				posYStart = pY;
				
				/*vector<xLine> p = getFastXLines(curObjID, pX, pY);
				
				for(int i=0; i<p.size(); ++i) {
					p[i].xStart += pX; p[i].xEnd += pX;
					p[i].yStart += pY; 	p[i].yEnd += pY;
				}
				
				xObj newObj(p, curObjID);
				
				MPT.drawObjs.push_back(newObj);*/
				
				updateDraw(hwnd, rect);
			}
			break;
		}
		
		case WM_MOUSEWHEEL: {
			short wheel_delta = GET_WHEEL_DELTA_WPARAM(wParam);
            
            if(wheel_delta > 0) {
				curObjID = (curObjID>=OBJ_COUNT)? OBJ_COUNT: ++curObjID;
			}
			else {
				curObjID = (curObjID==0)? 0: --curObjID;
			}
			updateDraw(hwnd, rect);
			break;
		}
		
		// Смена объекта при клике ПКМ
		case WM_RBUTTONDOWN: {
			posXStart = LOWORD(lParam);
			posYStart = HIWORD(lParam);
			
			/*curObjID = (curObjID>OBJ_COUNT)? 0: ++curObjID;*/
			updateDraw(hwnd, rect);
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
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

