#include <stdio.h>

struct Point {
	int x;
	int y;
};

struct Rect {
	Point ptLeftTop;
	Point ptRightBottom;
} rect, *ptrRect;

int main()
{
	rect.ptLeftTop.x = 10;
	rect.ptLeftTop.y = 20;
	rect.ptRightBottom.x = 100;
	rect.ptRightBottom.y = 200;

	ptrRect = &rect;

	printf("x1:%d, y1:%d, x2:%d, y2:%d \n",
		ptrRect->ptLeftTop.x, ptrRect->ptLeftTop.y,
		ptrRect->ptRightBottom.x, ptrRect->ptRightBottom.y);

	printf("size of rect   : %d \n", sizeof(rect));
	printf("size of ptrRect: %d \n\n\n", sizeof(ptrRect));
}