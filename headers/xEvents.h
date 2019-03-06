#ifndef XEVENTS_H_INC
#define XEVENTS_H_INC

#include "../stdafx.h"

class xEvents {
	public:
		virtual int onCreate(CREATESTRUCT *ct) = 0;
		virtual int onDestroy() = 0;
		virtual int onClose() { return 0x0EBA1; };
		virtual int onPaint() { return 0x0EBA1; };
		virtual int onCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) { return 0x0EBA1; };
		virtual int onMouseWhell(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) { return 0x0EBA1; };
		virtual int onKeyDown(int key, int flag) { return 0x0EBA1; };
		
		virtual int onMouseMove(int x, int y, int keys) { return 0x0EBA1; };
		
		virtual int onLButtonUp(int x, int y, int keys) { return 0x0EBA1; };
		virtual int onLButtonDown(int x, int y, int keys) { return 0x0EBA1; };
		virtual int onRButtonUp(int x, int y, int keys) { return 0x0EBA1; };
		virtual int onRButtonDown(int x, int y, int keys) { return 0x0EBA1; };
		
		
		int event(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
			int s = 0, pX=0, pY=0;
			
			switch(Message) {
				case WM_MOUSEMOVE:
				case WM_LBUTTONUP:
				case WM_LBUTTONDOWN:
				case WM_RBUTTONUP:
				case WM_RBUTTONDOWN: {
					pX = LOWORD(lParam);
					pY = HIWORD(lParam);
					break;
				}
			}
			
			switch(Message) {
				case WM_CREATE: {
					s = onCreate((CREATESTRUCT*) lParam);
					break;
				}
				case WM_DESTROY: {
					s = onDestroy();
					break;
				}
				case WM_CLOSE: {
					s = onClose();
					break;
				}
				case WM_PAINT: {
					s = onPaint();
					break;
				}
				case WM_COMMAND: {
					s = onCommand(hwnd, Message, wParam, lParam);				
					break;
				}
				case WM_MOUSEWHEEL: {
					s = onMouseWhell(hwnd, Message, wParam, lParam);
					break;
				}
				case WM_KEYDOWN: {
					s = onKeyDown(wParam, lParam);
					break;
				}
				
				case WM_MOUSEMOVE: {
					s = onMouseMove(pX, pY, wParam);				
					break;
				}
				case WM_LBUTTONUP: {
					s = onLButtonUp(pX, pY, wParam);	
					break;
				}
				case WM_LBUTTONDOWN: {
					s = onLButtonDown(pX, pY, wParam);	
					break;
				}
				case WM_RBUTTONUP: {
					s = onRButtonUp(pX, pY, wParam);	
					break;
				}
				case WM_RBUTTONDOWN: {
					s = onRButtonDown(pX, pY, wParam);	
					break;
				}
				
				
				default: {
					return DefWindowProc(hwnd, Message, wParam, lParam);
					break;
				}
			}
			if(s == 0x0EBA1)
				return DefWindowProc(hwnd, Message, wParam, lParam);
			return 0;
		}
};

#endif
