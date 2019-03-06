#ifndef XEVENTS_H_INC
#define XEVENTS_H_INC

#include "../stdafx.h"

/*struct Event {
	Event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) : hwnd (hwnd), msg (msg), wParam (wParam), lParam (lParam) { };
	
	HWND hwnd;
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
};*/

class xEvents {
	public:
		virtual int onCreate(CREATESTRUCT *ct) = 0;
		virtual int onDestroy() = 0;
		virtual int onPaint() { return 0x0EBA1; };
		virtual int onCommand(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) { return 0x0EBA1; };
		
	int event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		int s = 0;
		
		switch(msg) {
			case WM_CREATE: {
				s = onCreate((CREATESTRUCT*) lParam);
				break;
			}
			case WM_DESTROY: {
				s = onDestroy();
				break;
			}
			case WM_PAINT: {
				s = onPaint();
				break;
			}
			case WM_COMMAND: {
				s = onCommand(hwnd, msg, wParam, lParam);				
				break;
			}
			default: {
				return DefWindowProc(hwnd, msg, wParam, lParam);
				break;
			}
		}
		if(s == 0x0EBA1)
			return DefWindowProc(hwnd, msg, wParam, lParam);
		return 0;
	}
};

#endif
