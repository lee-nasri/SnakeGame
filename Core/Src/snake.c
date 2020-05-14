#include "snake.h"
#include "queue.h"

struct Queue* snake_x;
struct Queue* snake_y;
static volatile int snake_direction;
static volatile int score; /* Current score of game */
static int snake_head_x;
static int snake_head_y;
static int snake_tail_x;
static int snake_tail_y;

void snake_init(char scene[1920]){
	snake_x = createQueue(1000);
	snake_y = createQueue(1000);
	snake_direction = RIGHT;
	for (int x = 0; x < 5; ++x) { snake_enqueue(x, 0, scene); }
	scene[80*22 + 0] = 'S';
	scene[80*22 + 1] = 'c';
	scene[80*22 + 2] = 'o';
	scene[80*22 + 3] = 'r';
	scene[80*22 + 4] = 'e';
	scene[80*22 + 6] = ':';
	scene[80*22 + 8] = '0';
	scene[80*22 + 9] = '0';
	scene[80*22 + 10] = '0';
	snake_head_x = rear(snake_x);
	snake_head_y = rear(snake_y);
	snake_tail_x = front(snake_x);
	snake_tail_y = front(snake_y);
}

void snake_enqueue(int x, int y, char scene[1920]){
	if ((80*y + x) >= 1760) { x = 0; y = 0;}
	else if ((80*y + x) < 0) { x = 0; y = 0;}
	enqueue(snake_x, x);
	enqueue(snake_y, y);
	snake_head_x = rear(snake_x);
	snake_head_y = rear(snake_y);
	scene[80 * y + x] = '@';
}

void snake_dequeue(char scene[1920]){
	int x = front(snake_x); dequeue(snake_x);
	int y = front(snake_y); dequeue(snake_y);
	snake_tail_x = front(snake_x);
	snake_tail_y = front(snake_y);
	scene[80*y + x] = ' ';
}

void snake_setDirection(int direction) {

    /* Sets a legal direction for the snake. */
    /* Note that the snake cannot turn back on itself*/
    switch(direction) {
    case LEFT :
        if(snake_direction != RIGHT) {
            snake_direction = LEFT;
        }
        break;

    case RIGHT :
        if(snake_direction != LEFT) {
            snake_direction = RIGHT;
        }
        break;

    case UP :
        if(snake_direction != DOWN) {
            snake_direction = UP;
        }
        break;

    case DOWN :
        if(snake_direction != UP) {
            snake_direction = DOWN;
        }
        break;
    default :
        break;
    }

}

void snake_move(char scene[1920]) {

    /* Based on the snake direction, move head one coordinate*/
	int head_x = snake_head_x;
	int head_y = snake_head_y;

    switch(snake_direction) {
        /* UP and DOWN are y-axis roll-over 0-15 */
    case UP :
    	snake_enqueue(head_x, head_y - 1, scene);
    	snake_dequeue(scene);
        break;
    case DOWN :
    	snake_enqueue(head_x, head_y+1, scene);
    	snake_dequeue(scene);
        break;
    case LEFT :
    	snake_enqueue(head_x-1, head_y, scene);
    	snake_dequeue(scene);
        break;
    case RIGHT :
    	snake_enqueue(head_x+1, head_y, scene);
    	snake_dequeue(scene);
        break;
    default :
        break;
    }
}

void scene_setPixel(char scene[1920], int pixel){
	scene[pixel] = 'X';
}

void scene_mainmenu(char scene[1920]){
	/* For observing the beginning of a pixel */
	scene[0] = 'S'; scene[1] = 'T'; scene[2] = 'A'; scene[3] = 'R'; scene[4] = 'T';

	scene[80*11 + 36] = 'S';
	scene[80*11 + 37] = 'N';
	scene[80*11 + 38] = 'A';
	scene[80*11 + 39] = 'K';
	scene[80*11 + 40] = 'E';
	scene[80*11 + 43] = 'G';
	scene[80*11 + 44] = 'O';
}

void scene_clear(char scene[1920]){
	for(int i=0;i<1920; i++) scene[i] = ' ';
}


