#pragma once

#include "../stdafx.h"

#define MENU_EXIT 10001

#define MENU_BAR 10005
#define MENU_COLORS 10006
#define MENU_TOOLS 10007
#define MENU_CLEAR 10008

class xMenu {
	public:
		xMenu();
		void set(HWND hWnd);
		HMENU bar;
};

