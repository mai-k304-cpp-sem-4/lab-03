#pragma once

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
	virtual void show();
	virtual void hide();
	bool isVisible();
	void moveTo(int newX, int newY);
	void drug(int shift);
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
	int getHeight();
	int getWidth();
	bool onTriggerEnter(Figure* enterFigure);
};

class Glass : public Figure {
private:
	int** wallMatrix;
public:
	Glass(int initX = 0, int initY = 0, int initHeight = 60, int initWidth = 60);
	~Glass();
	virtual void show();
	virtual void hide();
};

class Drop : public Figure {
public:
	Drop(int initX = 0, int initY = 0, int initHeight = 40, int initWidth = 40);
	~Drop();
	virtual void show();
	virtual void hide();
};

class Wall : public Figure {
public:
	Wall(int initX = 0, int initY = 0, int initHeight = 100, int initWidth = 100);
	~Wall();
	virtual void show();
	virtual void hide();
};

#pragma once