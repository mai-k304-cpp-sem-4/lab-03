#include <windows.h>
#include <cmath>
#include "Point.h"
#include "Image.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

extern HDC hdc;

using namespace std;

extern Drop* drops[DROPS_COUNT]; // ћассив капель
extern int dropsId; // »ндекс предмета столкновени€
extern Glass* glases[GLASES_COUNT]; // ћассив рюмок
extern int dropCountGet; // ѕодсчЄт собраных капель

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

Botle::Botle(int initX, int initY, int initHeight, int initWidth) : Point(initX, initY) {
	height = initHeight;
	width = initWidth;
}

Botle::~Botle() { };

int Botle::getHeight() {
	return height;
}

int Botle::getWidth() {
	return width;
}

void Botle::neck() {
	if (visible == true) {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 7; //левый верхний угол
		r.top = y - height / 2 - 10;
		r.right = x + width / 7; //правый нижний
		r.bottom = y - height / 2;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(150, 100, 100)));
	}
	else {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 7; //левый верхний угол
		r.top = y - height / 2 - 10;
		r.right = x + width / 7; //правый нижний
		r.bottom = y - height / 2;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(12, 13, 13)));
	}
}

void Botle::cork() {
	if (visible == true) {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 7; //левый верхний угол
		r.top = y - height / 2;
		r.right = x + width / 7; //правый нижний
		r.bottom = y - height / 4;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(0, 150, 100)));
	}
	else {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 7; //левый верхний угол
		r.top = y - height / 2;
		r.right = x + width / 7; //правый нижний
		r.bottom = y - height / 4;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(12, 13, 13)));
	}
}

void Botle::body() {
	if (visible == true) {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 3; //левый верхний угол
		r.top = y - height / 4;
		r.right = x + width / 3; //правый нижний
		r.bottom = y + height / 3;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(0, 150, 100)));
	}
	else {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 3; //левый верхний угол
		r.top = y - height / 4;
		r.right = x + width / 3; //правый нижний
		r.bottom = y + height / 3;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(12, 13, 13)));
	}
}

void Botle::bottom() {
	if (visible == true) {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 3 - 3; //левый верхний угол
		r.top = y + height / 3;
		r.right = x + width / 3 + 3; //правый нижний
		r.bottom = y + height / 3 + 10;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(0, 100, 0)));
	}
	else {
		RECT r; //объ€вл€ем экзмепл€р структуры RECT - координаты пр€моугольника.
		r.left = x - width / 3 - 3; //левый верхний угол
		r.top = y + height / 3;
		r.right = x + width / 3 + 3; //правый нижний
		r.bottom = y + height / 3 + 10;
		FillRect(hdc, &r, (HBRUSH)CreateSolidBrush(RGB(12, 13, 13)));
	}
}

void Botle::show() {
	visible = true;
	neck();
	cork();
	body();
	bottom();
}

void Botle::hide() {
	visible = false;
	neck();
	cork();
	body();
	bottom();
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

void Glass::top(int _glassMatrixR[32][32], int _glassMatrixG[32][32], int _glassMatrixB[32][32]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 32; j++) {
			if ((_glassMatrixR[i][j] != 0) || (_glassMatrixG[i][j] != 0) || (_glassMatrixB[i][j] != 0)) {
				SetPixel(hdc, x + j, y + i, RGB(_glassMatrixR[i][j], _glassMatrixG[i][j], _glassMatrixB[i][j]));
			}
		}
	}
};

void Glass::bottom(int _glassMatrixR[32][32], int _glassMatrixG[32][32], int _glassMatrixB[32][32]) {
	for (int i = 24; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if ((_glassMatrixR[i][j] != 0) || (_glassMatrixG[i][j] != 0) || (_glassMatrixB[i][j] != 0)) {
				SetPixel(hdc, x + j, y + i, RGB(_glassMatrixR[i][j], _glassMatrixG[i][j], _glassMatrixB[i][j]));
			}
		}
	}
};

void Glass::left(int _glassMatrixR[32][32], int _glassMatrixG[32][32], int _glassMatrixB[32][32]) {
	for (int i = 8; i < 24; i++) {
		for (int j = 0; j < 12; j++) {
			if ((_glassMatrixR[i][j] != 0) || (_glassMatrixG[i][j] != 0) || (_glassMatrixB[i][j] != 0)) {
				SetPixel(hdc, x + j, y + i, RGB(_glassMatrixR[i][j], _glassMatrixG[i][j], _glassMatrixB[i][j]));
			}
		}
	}
};

void Glass::rigth(int _glassMatrixR[32][32], int _glassMatrixG[32][32], int _glassMatrixB[32][32]) {
	for (int i = 8; i < 24; i++) {
		for (int j = 24; j < 32; j++) {
			if ((_glassMatrixR[i][j] != 0) || (_glassMatrixG[i][j] != 0) || (_glassMatrixB[i][j] != 0)) {
				SetPixel(hdc, x + j, y + i, RGB(_glassMatrixR[i][j], _glassMatrixG[i][j], _glassMatrixB[i][j]));
			}
		}
	}
};

void Glass::middle(int _glassMatrixR[32][32], int _glassMatrixG[32][32], int _glassMatrixB[32][32]) {
	for (int i = 8; i < 24; i++) {
		for (int j = 12; j < 24; j++) {
			if ((_glassMatrixR[i][j] != 0) || (_glassMatrixG[i][j] != 0) || (_glassMatrixB[i][j] != 0)) {
				SetPixel(hdc, x + j, y + i, RGB(_glassMatrixR[i][j], _glassMatrixG[i][j], _glassMatrixB[i][j]));
			}
		}
	}
};

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
	top(Image::standrardGlassMatrixR, Image::standrardGlassMatrixG, Image::standrardGlassMatrixB);
	bottom(Image::standrardGlassMatrixR, Image::standrardGlassMatrixG, Image::standrardGlassMatrixB);
	left(Image::standrardGlassMatrixR, Image::standrardGlassMatrixG, Image::standrardGlassMatrixB);
	rigth(Image::standrardGlassMatrixR, Image::standrardGlassMatrixG, Image::standrardGlassMatrixB);
	middle(Image::standrardGlassMatrixR, Image::standrardGlassMatrixG, Image::standrardGlassMatrixB);

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
	top(Image::magicGlassMatrixR, Image::magicGlassMatrixG, Image::magicGlassMatrixB);
	bottom(Image::magicGlassMatrixR, Image::magicGlassMatrixG, Image::magicGlassMatrixB);
	left(Image::magicGlassMatrixR, Image::magicGlassMatrixG, Image::magicGlassMatrixB);
	rigth(Image::magicGlassMatrixR, Image::magicGlassMatrixG, Image::magicGlassMatrixB);
	middle(Image::magicGlassMatrixR, Image::magicGlassMatrixG, Image::magicGlassMatrixB);
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
	top(Image::fireMagicGlassMatrixR, Image::fireMagicGlassMatrixG, Image::fireMagicGlassMatrixB);
	bottom(Image::fireMagicGlassMatrixR, Image::fireMagicGlassMatrixG, Image::fireMagicGlassMatrixB);
	left(Image::fireMagicGlassMatrixR, Image::fireMagicGlassMatrixG, Image::fireMagicGlassMatrixB);
	rigth(Image::fireMagicGlassMatrixR, Image::fireMagicGlassMatrixG, Image::fireMagicGlassMatrixB);
	middle(Image::fireMagicGlassMatrixR, Image::fireMagicGlassMatrixG, Image::fireMagicGlassMatrixB);
}

void TFireMagicGlass::hide(void) {
	visible = false;
	Image::fireMagicGlassHide(hdc, x, y);
}

TPoisonGlass::TPoisonGlass(int initX, int initY, int initHeight, int initWidth) : Glass(initX, initY, initHeight, initWidth) {
	id = 4;
}

TPoisonGlass::~TPoisonGlass(void) { };

void TPoisonGlass::show(void) {
	visible = true;
	top(Image::poisonGlassMatrixR, Image::poisonGlassMatrixG, Image::poisonGlassMatrixB);
	bottom(Image::poisonGlassMatrixR, Image::poisonGlassMatrixG, Image::poisonGlassMatrixB);
	left(Image::poisonGlassMatrixR, Image::poisonGlassMatrixG, Image::poisonGlassMatrixB);
	rigth(Image::poisonGlassMatrixR, Image::poisonGlassMatrixG, Image::poisonGlassMatrixB);
	middle(Image::poisonGlassMatrixR, Image::poisonGlassMatrixG, Image::poisonGlassMatrixB);
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
	Image::fireMagicDropShow(hdc, x, y);
}

void TFireMagicDrop::hide(void) {
	visible = false;
	Image::fireMagicDropHide(hdc, x, y);
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