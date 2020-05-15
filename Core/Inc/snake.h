#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

#define UP    1 /* Directions of snake */
#define RIGHT 2
#define DOWN  3
#define LEFT  4
#define START_X 15 /* Starting coordinates of snake */
#define START_Y 12

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void snake_init(char scene[1920]);

void snake_enqueue(int x, int y, char scene[1920]);

void snake_dequeue(char scene[1920]);

void snake_setDirection(int direction);

void snake_move(char scene[1920]) ;

int snake_foodScore(int x, int y, char scene[1920]);

void snake_feed(int foodScore, char scene[1920]);

void snake_gameOver(char scene[1920]);

void scene_setPixelX(int x1, int x2, int y, char scene[1920], char text[], int size);

void scene_setScore(char scene[1920]);

void scene_mainmenu(char scene[1920]);

void scene_clear(char scene[1920]);

char intTOchar(int integers);

#endif /* SRC_SNAKE_H_ */
