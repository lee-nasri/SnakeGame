#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

#define UP    1 /* Directions of snake */
#define RIGHT 2
#define DOWN  3
#define LEFT  4
#define START_X 15 /* Starting coordinates of snake */
#define START_Y 12

void snake_init(char scene[1920]);

void snake_enqueue(int x, int y, char scene[1920]);

void snake_dequeue(char scene[1920]);

void snake_setDirection(int direction);

void snake_move(char scene[1920]) ;

void scene_setPixel(char scene[1920], int pixel);

void scene_mainmenu(char scene[1920]);

void scene_clear(char scene[1920]);

#endif /* SRC_SNAKE_H_ */
