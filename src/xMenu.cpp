#include "xMenu.h"


xMenu::xMenu() {
	bar = CreateMenu();
	HMENU sub;
	
	sub = CreateMenu();
	AppendMenu(sub, MF_STRING, MENU_COLORS, "Color");
	
	AppendMenu(bar, MF_POPUP, (UINT_PTR)sub, "Tools");
	
	
	
	AppendMenu(bar, MF_HELP|MF_STRING, (UINT_PTR)MENU_EXIT, "Exit");
}
void xMenu::set(HWND hwnd) {
	SetMenu(hwnd, bar);
}
