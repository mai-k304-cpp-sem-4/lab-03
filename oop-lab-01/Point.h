#pragma once
#define DROPS_COUNT 4
#define GLASES_COUNT 4
#define X_MAX 1000
#define X_MIN 0
#define Y_MAX 1000
#define Y_MIN 0

class Location {
protected:
	int x;
	int y;
public:
	Location(int InitX, int InitY);
	~Location();
	int getX();
	int getY();
};

class Point : public Location {
protected:
	bool visible;
public:
	Point(int initX = 0, int initY = 0);
	~Point();
	virtual void show() = 0;
	virtual void hide() = 0;
	bool isVisible();
	void moveTo(int newX, int newY);
	virtual void drug(int shift);
};

class Figure : public Point {
protected:
	int height;
	int width;
public:
	Figure(int initX = 0, int initY = 0, int initHeight = 0, int initWidth = 0);
	~Figure();
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void drug(int shift);
	int getHeight();
	int getWidth();
	bool ñollision(Figure* enterFigure);
};

class Glass : public Figure {
protected:
	int id;
public:
	Glass(int initX = 0, int initY = 0, int initHeight = 32, int initWidth = 32);
	~Glass();
	virtual void show();
	virtual void hide();
	int getId();
};

class TStandardGlass : public Glass {
public:
	TStandardGlass(int initX = 0, int initY = 0, int initHeight = 32, int initWidth = 32);
	~TStandardGlass();
	virtual void show();
	virtual void hide();
};

class TMagicGlass : public Glass {
public:
	TMagicGlass(int initX = 0, int initY = 0, int initHeight = 32, int initWidth = 32);
	~TMagicGlass();
	virtual void show();
	virtual void hide();
};

class TFireMagicGlass : public Glass {
public:
	TFireMagicGlass(int initX = 0, int initY = 0, int initHeight = 32, int initWidth = 32);
	~TFireMagicGlass();
	virtual void show();
	virtual void hide();
};

class TPoisonGlass : public Glass {
public:
	TPoisonGlass(int initX = 0, int initY = 0, int initHeight = 32, int initWidth = 32);
	~TPoisonGlass();
	virtual void show();
	virtual void hide();
};


class Drop : public Figure {
protected:
	int id;
public:
	Drop(int initX = 0, int initY = 0, int initHeight = 16, int initWidth = 16);
	~Drop();
	virtual void show();
	virtual void hide();
	int getId();
};

class TStandardDrop : public Drop {
public:
	TStandardDrop(int initX = 0, int initY = 0, int initHeight = 16, int initWidth = 16);
	~TStandardDrop();
	virtual void show();
	virtual void hide();
};

class TMagicDrop : public Drop {
public:
	TMagicDrop(int initX = 0, int initY = 0, int initHeight = 16, int initWidth = 16);
	~TMagicDrop();
	virtual void show();
	virtual void hide();
};

class TFireMagicDrop : public TMagicDrop {
public:
	TFireMagicDrop(int initX = 0, int initY = 0, int initHeight = 16, int initWidth = 16);
	~TFireMagicDrop();
	virtual void show();
	virtual void hide();
};

class TPoisonDrop : public Drop {
public:
	TPoisonDrop(int initX = 0, int initY = 0, int initHeight = 16, int initWidth = 16);
	~TPoisonDrop();
	virtual void show();
	virtual void hide();
};

#pragma once