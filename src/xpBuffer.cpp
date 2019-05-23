#include "xpBuffer.h"

xpBuffer::xpBuffer(HWND hWnd, int wh, int hg)
	: hWnd (hWnd), width(wh), height(hg) {

	hDC = GetDC(hWnd);
	
	hMemDC = CreateCompatibleDC(hDC);
	renderDC = CreateCompatibleDC(hDC);
	
	
	// oldMem = (HBITMAP) SelectObject(renderDC, create32DIB(renderDC, width, height, &memBytes));
	// oldRenderer = (HBITMAP) SelectObject(renderDC, create32DIB(renderDC, width, height, &rendererBytes));
	
	drawRect.left = 0;
	drawRect.right = width;
	drawRect.top = 0;
	drawRect.bottom = height;
	
	//BitBlt()
}

void xpBuffer::DrawFigure(xDrawLib *fig) {
	if(figures.size() > 10) {
		
	}
	
	fig->Draw(hMemDC);
	
}


void xpBuffer::DrawFigures(HDC xHDC) {
	RECT rect;
	GetClientRect(hWnd, &rect);
	
	// Draw objects
	for(int doID = 0; doID < drawObjs.size(); doID++) {
		
		char buf[50];
		sprintf(buf, "S: [%d]", doID);
		//cc(buf);

		xObj curObj = drawObjs[doID];
		// ... set pen and other
		bool selected = (selectableObjID != 0 && doID == selectableObjID-1);
		POINT pos = curObj.pos;
		int msize = curObj.size;	
		POINT rotation = curObj.rotation;	
						
		// Draw object line
		for(int i=0; i<curObj.lines.size(); i++) {
			xLine p = curObj.lines[i];
			
			if(selected) {
				HPEN selPen = (HPEN) CreatePen(PS_SOLID, 3, RGB(240, 100, 80));
				hOldPen = (HPEN) SelectObject(xHDC, selPen);
			}
			else if(p.pen != NULL) {
				hOldPen = (HPEN) SelectObject(xHDC, p.pen);
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
				MoveToEx(xHDC, p.xStart, p.yStart, NULL);
				
			LineTo(xHDC, p.xEnd, p.yEnd);
			
			if(hOldPen) {
				SelectObject(xHDC, hOldPen);
				hOldPen = NULL;
			}
			
		}
	}
	
	// BitBlt(renderDC, 0, 0, rect.right, rect.bottom, xHDC, 0, 0, SRCCOPY);
	// DeleteDC(xHDC);
}


void xpBuffer::DrawFullPaint() {
	RECT rect;
	GetClientRect(hWnd, &rect);
	
	DrawFigures(hDC);
	
	
	//BitBlt(hDC, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);
	//DeleteDC(hMemDC);
		
	if(previewObj != NULL) {
		
		// Draw preview
		HPEN prevPen = CreatePen(PS_SOLID, 3, RGB(130, 150, 150));
		hOldPen = (HPEN) SelectObject(hDC, prevPen);
		POINT pos = previewObj->pos;
		int msize = previewObj->size;
		POINT rotation = previewObj->rotation;
		
		for(int i=0; i<previewObj->lines.size(); i++) {
			xLine p = previewObj->lines[i];
			
			// ...
			p.xStart *= msize; p.xEnd *= msize;
			p.yStart *= msize; p.yEnd *= msize;
			
			p.xStart += pos.x; p.xEnd += pos.x;
			p.yStart += pos.y; p.yEnd += pos.y;
			
			if(!p.nup)
				MoveToEx(hDC, p.xStart, p.yStart, NULL);
			LineTo(hDC, p.xEnd, p.yEnd);
			
		}
		
	
		if(hOldPen) {
			SelectObject(hDC, hOldPen);
			hOldPen = NULL;
		}
	}


	/*char buf[50];
	sprintf(buf, "WH: [%d x %d]", width, height);
	//cc(buf);

	
	SetStretchBltMode(hDC, COLORONCOLOR);
	// renderDC -> hDC
	StretchBlt(hDC, 0, 0, width, height, renderDC, 0, 0, width, height, SRCCOPY);*/
	
}












