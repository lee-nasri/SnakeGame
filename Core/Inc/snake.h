#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

#define UP    1 /* Directions of snake */
#define RIGHT 2
#define DOWN  3
#define LEFT  4
#define START_X 15 /* Starting coordinates of snake */
#define START_Y 12

void snake_init(void);

void snake_enqueue(int x, int y);

void snake_dequeue();

void snake_set_direction(int direction);

static void snake_move(void);

#endif /* SRC_SNAKE_H_ */
