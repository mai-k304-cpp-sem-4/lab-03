#include <windows.h>
#include <cmath>
#include "Point.h"
#include "Image.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

extern HDC hdc;

using namespace std;

extern Drop* drops[DROPS_COUNT]; // Массив капель
extern int dropsId; // Индекс предмета столкновения
extern Glass* glases[GLASES_COUNT]; // Массив рюмок
extern int dropCountGet; // Подсчёт собраных капель

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

void Figure::drug(int shift) {
	if (KEY_DOWN(VK_DOWN)) {
		moveTo(x, y + shift);
		for (int i = 0; i < DROPS_COUNT; i++) {
			if (drops[i]->сollision(this)) {
				dropsId = i;
				dropCountGet++;
				drops[i]->moveTo(rand() % 800 + 30, rand() % 400 + 3);
				for (int j = 0; j < GLASES_COUNT; j++) {
					glases[j]->moveTo(this->getX(), this->getY());
					glases[j]->hide();
				}
				return;
			}
		}
	}
	if (KEY_DOWN(VK_UP)) {
		moveTo(x, y - shift);
		for (int i = 0; i < DROPS_COUNT; i++) {
			if (drops[i]->сollision(this)) {
				dropsId = i;
				dropCountGet++;
				drops[i]->moveTo(rand() % 800 + 30, rand() % 400 + 3);
				for (int j = 0; j < GLASES_COUNT; j++) {
					glases[j]->moveTo(this->getX(), this->getY());
					glases[j]->hide();
				}
				return;
			}
		}
	}
	if (KEY_DOWN(VK_RIGHT)) {
		moveTo(x + shift, y);
		for (int i = 0; i < DROPS_COUNT; i++) {
			if (drops[i]->сollision(this)) {
				dropsId = i;
				dropCountGet++;
				drops[i]->moveTo(rand() % 800 + 30, rand() % 400 + 3);
				for (int j = 0; j < GLASES_COUNT; j++) {
					glases[j]->moveTo(this->getX(), this->getY());
					glases[j]->hide();
				}
				return;
			}
		}
	}
	if (KEY_DOWN(VK_LEFT)) {
		moveTo(x - shift, y);
		for (int i = 0; i < DROPS_COUNT; i++) {
			if (drops[i]->сollision(this)) {
				dropsId = i;
				dropCountGet++;
				drops[i]->moveTo(rand() % 800 + 30, rand() % 400 + 3);
				for (int j = 0; j < GLASES_COUNT; j++) {
					glases[j]->moveTo(this->getX(), this->getY());
					glases[j]->hide();
				}
				return;
			}
		}
	}
}

int Figure::getHeight(void) { return height; }

int Figure::getWidth(void) { return width; }

bool Figure::сollision(Figure* enterFigure) {

	int enterFigureX = enterFigure->getX(), enterFigureY = enterFigure->getY();
	int enterFigureWidth = enterFigure->getWidth() / 2;
	int enterFigureHeight = enterFigure->getHeight() / 2;
	bool hitX = x + width / 2 >= enterFigureX - enterFigureWidth && x <= enterFigureX + enterFigureWidth;
	bool hitY = y + height / 2 >= enterFigureY - enterFigureHeight && y <= enterFigureY + enterFigureHeight;

	return hitX && hitY;
}

Glass::Glass(int initX, int initY, int initHeight, int initWidth) : Figure(initX, initY, initHeight, initWidth) {
	id = 0;
}

Glass::~Glass(void) { };

void Glass::show(void) {
	visible = true;
	Image::standrardGlassShow(hdc, x, y);
}

void Glass::hide(void) {
	visible = false;
	Image::standrardGlassHide(hdc, x, y);
}

int Glass::getId(void) {
	return id;
};

TStandardGlass::TStandardGlass(int initX, int initY, int initHeight, int initWidth) : Glass(initX, initY, initHeight, initWidth) {
	id = 1;
}

TStandardGlass::~TStandardGlass(void) { };

void TStandardGlass::show(void) {
	visible = true;
	Image::standrardGlassShow(hdc, x, y);
}

void TStandardGlass::hide(void) {
	visible = false;
	Image::standrardGlassHide(hdc, x, y);
}

TMagicGlass::TMagicGlass(int initX, int initY, int initHeight, int initWidth) : Glass(initX, initY, initHeight, initWidth) {
	id = 2;
}

TMagicGlass::~TMagicGlass(void) { };

void TMagicGlass::show(void) {
	visible = true;
	Image::magicGlassShow(hdc, x, y);
}

void TMagicGlass::hide(void) {
	visible = false;
	Image::magicGlassHide(hdc, x, y);
}

TFireMagicGlass::TFireMagicGlass(int initX, int initY, int initHeight, int initWidth) : Glass(initX, initY, initHeight, initWidth) {
	id = 3;
}

TFireMagicGlass::~TFireMagicGlass(void) { };

void TFireMagicGlass::show(void) {
	visible = true;
	Image::magicDropShow(hdc, x, y);
}

void TFireMagicGlass::hide(void) {
	visible = false;
	Image::magicDropHide(hdc, x, y);
}

TPoisonGlass::TPoisonGlass(int initX, int initY, int initHeight, int initWidth) : Glass(initX, initY, initHeight, initWidth) {
	id = 4;
}

TPoisonGlass::~TPoisonGlass(void) { };

void TPoisonGlass::show(void) {
	visible = true;
	Image::poisonGlassShow(hdc, x, y);
}

void TPoisonGlass::hide(void) {
	visible = false;
	Image::poisonGlassHide(hdc, x, y);
}

Drop::Drop(int initX, int initY, int initHeight, int initWidth) : Figure(initX, initY, initHeight, initWidth) {
	id = 0;
}

Drop::~Drop(void) { };

void Drop::show(void) {
	visible = true;
}

void Drop::hide(void) {
	visible = false;
}

int Drop::getId(void) {
	return id;
}

TStandardDrop::TStandardDrop(int initX, int initY, int initHeight, int initWidth) : Drop(initX, initY, initHeight, initWidth) {
	id = 1;
}

TStandardDrop::~TStandardDrop(void) { };

void TStandardDrop::show(void) {
	visible = true;
	Image::standardDropShow(hdc, x, y);
}

void TStandardDrop::hide(void) {
	visible = false;
	Image::standardDropHide(hdc, x, y);
}

TMagicDrop::TMagicDrop(int initX, int initY, int initHeight, int initWidth) : Drop(initX, initY, initHeight, initWidth) {
	id = 2;
}

TMagicDrop::~TMagicDrop(void) { };

void TMagicDrop::show(void) {
	visible = true;
	Image::magicDropShow(hdc, x, y);
}

void TMagicDrop::hide(void) {
	visible = false;
	Image::magicDropHide(hdc, x, y);
}

TFireMagicDrop::TFireMagicDrop(int initX, int initY, int initHeight, int initWidth) : TMagicDrop(initX, initY, initHeight, initWidth) {
	id = 3;
}

TFireMagicDrop::~TFireMagicDrop(void) { };

void TFireMagicDrop::show(void) {
	visible = true;
	Image::magicGlassShow(hdc, x - 8, y - 8);
	Image::magicDropShow(hdc, x, y);
}

void TFireMagicDrop::hide(void) {
	visible = false;
	Image::magicGlassHide(hdc, x - 8, y - 8);
	Image::magicDropHide(hdc, x, y);
}


TPoisonDrop::TPoisonDrop(int initX, int initY, int initHeight, int initWidth) : Drop(initX, initY, initHeight, initWidth) {
	id = 4;
}

TPoisonDrop::~TPoisonDrop(void) { };

void TPoisonDrop::show(void) {
	visible = true;
	Image::poisonDropShow(hdc, x, y);
}

void TPoisonDrop::hide(void) {
	visible = false;
	Image::poisonDropHide(hdc, x, y);
}