#ifndef XMENU_H_INC
#define XMENU_H_INC

#include "../stdafx.h"

#define MENU_TOOLS 10005
#define MENU_COLORS 10006
#define MENU_EXIT 10001

class xMenu {
	public:
		xMenu();
		void set(HWND);
		HMENU bar;
};



#endif
