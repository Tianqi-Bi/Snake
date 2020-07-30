#include<cstdio>
#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "conio.h"

using namespace std;

const int X = 15;
const int Y = 20;

bool ifover(int);
void out(int);

int map[X][Y];

struct point {
	int x;
	int y;
};

struct part {
	point self;
	//point pre;
	bool head;
}snake[100];

int main() {
	srand((unsigned)time(NULL));
	snake[1].head = true;
	snake[1].self.x = X / 2;
	snake[1].self.y = Y / 2;
	snake[2].self.x = snake[1].self.x - 1;
	snake[2].self.y = snake[1].self.y;
	snake[0].self.x = X / 2;
	snake[0].self.y = Y / 2 + 3;
	//int direction = 0;
	int length = 2;
	int tmp;
	char in = 'd';
	while (ifover(length)) {
		cout << "\033[2J\033[0;0H";

		tmp = length;
		while(!snake[tmp].head){
			snake[tmp].self.x = snake[tmp - 1].self.x;
			snake[tmp].self.y = snake[tmp - 1].self.y;
			tmp--;
		}
		snake[length].head = false;
		if (kbhit()) {
			in = getch();
		}
		switch (in)
		{
		case 'd':
			snake[1].self.y++;
			break;
		case 's':
			snake[1].self.x++;
			break;
		case 'a':
			snake[1].self.y--;
			break;
		case 'w':
			snake[1].self.x--;
			break;
		}
		if (snake[1].self.x == snake[0].self.x && snake[1].self.y == snake[0].self.y) {
			snake[0].self.x = rand() % X;
			snake[0].self.y = rand() % Y;
			length++;
			snake[length].self.x = snake[length - 2].self.x;
			snake[length].self.y = snake[length - 2].self.y;
			//snake[length].head = true;
		}
		out(length);
		Sleep(700);
	}
}

bool ifover(int length){
	for (int i = 4; i <= length; i++) {
		if (snake[1].self.x == snake[i].self.x && snake[1].self.y == snake[i].self.y) {
			return false;
		}
	}
	if (snake[1].self.x < 0 || snake[1].self.y >= Y || snake[1].self.x >= X || snake[1].self.y < 0) {
		return false;
	}
	return true;
}

void out(int length) {
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			map[i][j] = 0;
		}
	}
	for (int i = 2; i <= length; i++) {
		map[snake[i].self.x][snake[i].self.y] = 1;
	}
	map[snake[1].self.x][snake[1].self.y] = 2;
	map[snake[0].self.x][snake[0].self.y] = 3;
	for (int i = 0; i < Y + 2; i++)
	{
		printf("\033[2m■\033[0m");
	}
	printf("\n");
	for (int i = 0; i < X; i++) {
		printf("\033[2m■\033[0m");
		for (int j = 0; j < Y; j++) {
			switch (map[i][j])
			{
			case 0:
				printf("\033[40;30m■\033[0m");//空
				break;
			case 1:
				printf("\033[40;37m■\033[0m");//身
				break;
			case 2:
				printf("\033[40;31m■\033[0m");//头
				break;
			case 3:
				printf("\033[40;33m■\033[0m");//点
				break;
			}
		}
		printf("\033[2m■\033[0m\n");
	}
	for (int i = 0; i < Y + 2; i++)
	{
		printf("\033[2m■\033[0m");
	}
	printf("\nscore:%d", length - 2);
	return;
}