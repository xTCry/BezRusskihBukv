#include "stdafx.h"
#include "main.h"
#include "xEditor.h"
#include "xSColor.h"
#include "xTools.h"


/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	int
		sizeW = GetSystemMetrics(SM_CXSCREEN)/2,
		sizeH = GetSystemMetrics(SM_CYSCREEN)/2,
		wPosX = sizeW/2,
		wPosY = sizeH/2;
	
	// Calc mouse pos
	POINT curPos;
	if(GetCursorPos(&curPos)) {
		
		char buf[50];
		sprintf(buf, "Mouse pos: [%d, %d]", curPos.x, curPos.y);
		//cc(buf);
		
		// for debg
		curPos.x = 3700;
		
		HMONITOR mon = MonitorFromPoint(curPos, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi;
		mi.cbSize = sizeof(MONITORINFO);
		GetMonitorInfo(mon, &mi);
		
		int pX = mi.rcWork.left,
			pY = mi.rcWork.top;
		
		sizeW = (mi.rcWork.right - mi.rcWork.left)/2;
		sizeH = (mi.rcWork.bottom - mi.rcWork.top)/2;
		
		wPosX = pX+sizeW/2;
		wPosY = pY+sizeH/2;
	}
	
	
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
	
	// Reg xTools Class
	wc.lpfnWndProc	 = xToolsWndProc; /* This is where we will send messages to */
	wc.lpszClassName = xToolsClassName;
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

void cc(LPCSTR msg) {
	MessageBox(NULL, msg, "Debug", MB_ICONASTERISK|MB_OK);
};


