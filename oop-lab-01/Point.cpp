#include <windows.h>
#include <cmath>
#include "Point.h"
#include "Image.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

extern HDC hdc;

using namespace std;

Location::Location(int x, int y) : x(x), y(y) { };

Location::~Location(void) { };

int Location::getX(void) { return x; };	

int Location::getY(void) { return y; };

Point::Point(int initX, int initY) : Location(initX, initY) { visible = false; }

Point::~Point(void) { }

void Point::show(void) {
	visible = true;
	SetPixel(hdc, x, y, RGB(255, 0, 0));
	SetPixel(hdc, x + 1, y, RGB(255, 0, 0));
	SetPixel(hdc, x, y + 1, RGB(255, 0, 0));
	SetPixel(hdc, x + 1, y + 1, RGB(255, 0, 0));
}

void Point::hide(void) {
	visible = false;
	SetPixel(hdc, x, y, RGB(0, 0, 255));
	SetPixel(hdc, x + 1, y, RGB(0, 0, 255));
	SetPixel(hdc, x, y + 1, RGB(0, 0, 255));
	SetPixel(hdc, x + 1, y + 1, RGB(0, 0, 255));
}

bool Point::isVisible(void) { return visible; };

void Point::moveTo(int newX, int newY) {
	hide();
	x = newX;
	y = newY;
	show();
};

void Point::drug(int shift) {
	if (KEY_DOWN(VK_DOWN))
		moveTo(x, y + shift);
	if (KEY_DOWN(VK_UP))
		moveTo(x, y - shift);
	if (KEY_DOWN(VK_RIGHT))
		moveTo(x + shift, y);
	if (KEY_DOWN(VK_LEFT))
		moveTo(x - shift, y);
}

Figure::Figure(int initX, int initY, int initHeight, int initWidth) : Point(initX, initY) {
	height = initHeight;
	width = initWidth;
}

Figure::~Figure() { };

int Figure::getHeight(void) { return height; }

int Figure::getWidth(void) { return width; }

bool Figure::onTriggerEnter(Figure* enterFigure) {
	int figureX = enterFigure->getX(), figureY = enterFigure->getY();
	int figureHeight = enterFigure->getHeight() / 2;
	int figureWidth = enterFigure->getWidth() / 2;
	bool hitX = x + width / 2 >= figureX - figureWidth && x - width / 2 <= figureX + figureWidth;
	bool hitY = y + height / 2 >= figureY - figureHeight && y - height / 2 <= figureY + figureHeight;

	if (hitX && hitY) {
		return true;
	}
	return false;
}

Glass::Glass(int initX, int initY, int initHeight, int initWidth) : Figure(initX, initY, initHeight, initWidth) { }

Glass::~Glass(void) { };

void Glass::show(void) {
	visible = true;
	Image::glassShow(hdc, x, y);
}

void Glass::hide(void) {
	visible = false;
	Image::glassHide(hdc, x, y);
}

Drop::Drop(int initX, int initY, int initHeight, int initWidth) : Figure(initX, initY, initHeight, initWidth) { }

Drop::~Drop(void) { };

void Drop::show(void) {
	visible = true;
	Image::dropShow(hdc, x, y);
}

void Drop::hide(void) {
	visible = false;
	Image::dropHide(hdc, x, y);
}

Wall::Wall(int initX, int initY, int initHeight, int initWidth) : Figure(initX, initY, initHeight, initWidth) { }

Wall::~Wall(void) { };

void Wall::show(void) {
	visible = true;
	Image::wallShow(hdc, x, y);
}

void Wall::hide(void) {
	visible = false;
	Image::wallHide(hdc, x, y);
}