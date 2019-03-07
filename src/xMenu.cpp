#include "xMenu.h"


xMenu::xMenu() {
	bar = CreateMenu();
	HMENU sub;
	
	sub = CreateMenu();
	AppendMenu(sub, MF_STRING, MENU_COLORS, "Color");
	AppendMenu(sub, MF_STRING, MENU_TOOLS, "Tools");
	AppendMenu(sub, MF_STRING, MENU_CLEAR, "Clear");
	
	AppendMenu(bar, MF_POPUP, (UINT_PTR)sub, "Menu");
	
	
	// Right Exit
	AppendMenu(bar, MF_HELP|MF_STRING, (UINT_PTR)MENU_EXIT, "Exit");
}
void xMenu::set(HWND hWnd) {
	SetMenu(hWnd, bar);
}
