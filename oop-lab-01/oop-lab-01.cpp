#pragma once    
#include <windows.h>
#include <conio.h>
#include <iostream>    
using namespace std;
#include "Point.h"
#include "GetConlWin.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

Drop* drops[DROPS_COUNT]; // Массив капель
int dropsId = 0; // Индекс предмета столкновения
Glass* glases[GLASES_COUNT]; // Массив рюмок
int dropCountGet = 0; // Подсчёт собранных капель

HDC hdc;
void main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));
	//cout << "Введите размер шага: ";
	int shift = 8;
	//cin >> shift;
	int x0 = 130, y0 = 250; // Начальные координаты
	HWND hwnd = GetConcolWindow();

	// Матрица перехода (по строкам капли, по столбцам рюмки)
	int matr_per[GLASES_COUNT][DROPS_COUNT] = {
		{0, 0, 2, 0},
		{1, 1, 2, 0},
		{0, 2, 0, 3},
		{3, 0, 2, 3}
	};

	if (hwnd != NULL) {
		hdc = GetWindowDC(hwnd);
		if (hdc != 0) {
			TStandardGlass SGlass(x0, y0);
			TMagicGlass MGlass(x0, y0);
			TFireMagicGlass FMGlass(x0, y0);
			TPoisonGlass PGlass(x0, y0);
			glases[0] = &SGlass;
			glases[1] = &MGlass;
			glases[2] = &FMGlass;
			glases[3] = &PGlass;
			Glass* pGlass; // Указатель на текущий объект
			pGlass = glases[0];
			pGlass->show();

			TStandardDrop SDrop(rand() % 800 + 30, rand() % 400 + 3);
			TMagicDrop MDrop(rand() % 800 + 30, rand() % 400 + 3);
			TFireMagicDrop FMDrop(rand() % 800 + 30, rand() % 400 + 3);
			TPoisonDrop PDrop(rand() % 800 + 30, rand() % 400 + 3);
			drops[0] = &SDrop;
			drops[1] = &MDrop;
			drops[2] = &FMDrop;
			drops[3] = &PDrop;
			drops[0]->show();
			drops[1]->show();
			drops[2]->show();
			drops[3]->show();

			while (!KEY_DOWN(49)) {
				// Перемещение по карте капель
				for (int i = 0; i < DROPS_COUNT; i++) {
					drops[i]->moveTo(drops[i]->getX() + rand() % 5 - 2, drops[i]->getY() + rand() % 5 - 2);
					// Проверка на выход из зоны видимости консоли
					if ((drops[i]->getX() > X_MAX) || (drops[i]->getX() < X_MIN) || (drops[i]->getY() > Y_MAX) || (drops[i]->getY() < Y_MIN)) {
						drops[i]->moveTo(100 + rand() % 1000, 100); // Если вышли то перемещаем их в зону видимости
					}
				}
				pGlass->drug(shift);
				// Переход к новому объекту
				if (dropsId != -1)
					pGlass = glases[matr_per[dropsId][pGlass->getId() - 1]]; // Переход к новому объекту
				dropsId = -1;
				pGlass->show();

				//if (dropCountGet == 7) exit(0);
			}
		}
	}
}