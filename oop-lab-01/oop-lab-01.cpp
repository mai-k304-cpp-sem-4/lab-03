#pragma once    
#include <windows.h>
#include <conio.h>
#include <iostream>    
using namespace std;
#include "Point.h"
#include "GetConlWin.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

const int dropCount = 7;
const int wallWigth = 5, wallHeight = 10;

HDC hdc;
void main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));
	cout << "Введите размер шага: ";
	int shift = 10;
	cin >> shift;
	int x0 = 130, y0 = 250; // Начальные координаты
	HWND hwnd = GetConcolWindow();
	if (hwnd != NULL) {
		hdc = GetWindowDC(hwnd);
		if (hdc != 0) {

			Wall wallArr[wallWigth][wallHeight];
			bool wallMatrix[wallWigth][wallHeight] = {
				//{false, false, false, false, false, false, false, false, false},
				{true, true, true, true, true, true, true, true, true},
				{true, false, false, false, false, false, false, false, true},
				{true, false, true, false, true, false, true, false, true},
				{true, false, false, false, false, false, false, false, true},
				//{false, false, false, false, false, false, false, false, false}
				{true, true, true, true, true, true, true, true, true}
			};
			for (int i = 0; i < wallHeight; i++) {
				for (int j = 0; j < wallWigth; j++) {
					if (wallMatrix[j][i] == true) {
						wallArr[j][i].moveTo(i * 100 + 30, j * 100 + 30);
					}
					else {
						wallArr[j][i] = NULL;
					}
				}
			}

			Glass BGlass(x0, y0);
			BGlass.show();

			Drop dropArr[dropCount];
			for (int i = 0; i < dropCount; i++) {
				bool f = false;
				while (f == false) {
					f = true;
					int newX = rand() % 800 + 30;
					int newY = rand() % 500 + 3;
					dropArr[i].moveTo(newX, newY);
					for (int k = 0; k < wallHeight; k++) {
						for (int j = 0; j < wallWigth; j++) {
							Figure* tempWall = &wallArr[j][k];
							if (dropArr[i].onTriggerEnter(tempWall) == true)
								f = false;
						}
					}
				}
			}

			for (int i = 0; i < wallHeight; i++) {
				for (int j = 0; j < wallWigth; j++) {
					wallArr[j][i].show();
				}
			}
			int dropCountGet = 0;
			while (!KEY_DOWN(49)) {
				BGlass.drug(shift);
				for (int i = 0; i < dropCount; i++) {
					if (BGlass.onTriggerEnter(&dropArr[i])) {
						dropArr[i].hide();
						dropArr[i] = NULL;
						dropCountGet++;
					}
				}
				for (int i = 0; i < wallHeight; i++) {
					for (int j = 0; j < wallWigth; j++) {
						if (BGlass.onTriggerEnter(&wallArr[j][i])) {
							wallArr[j][i].show();
							//cout << "G";
						}
					}
				}
				if (dropCountGet == dropCount) exit(0);
			}
		}
	}
}