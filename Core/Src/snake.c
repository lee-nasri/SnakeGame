#include "snake.h"

struct Queue* snake_x;
struct Queue* snake_y;
static volatile int snake_direction = RIGHT; /* Direction snake should move next */
static volatile int score; /* Current score of game */
static int *snake_head_x;
static int *snake_head_y;
static int *snake_tail_x;
static int *snake_tail_y;
char scene[1920];

// declare function before call
void snake_enqueue(int, int);
static void snake_move();

void snake_init(){
	snake_x = createQueue(1000);
	snake_y = createQueue(1000);
	scene_clear();
	for (int i = 0; i < 5; ++i) { snake_enqueue(0, i); }
	snake_head_x = rear(snake_x);
	snake_head_y = rear(snake_y);
	snake_tail_x = front(snake_x);
	snake_tail_y = front(snake_y);
}

void scene_mainmenu(){
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

void snake_enqueue(int x, int y){
	enqueue(snake_x, x);
	enqueue(snake_y, y);
	snake_head_x = rear(snake_x);
	snake_head_y = rear(snake_y);
	scene[80*x + y] = '@';
}

void snake_dequeue(){
	int x = front(snake_x); dequeue(snake_x);
	int y = front(snake_y); dequeue(snake_y);
	snake_tail_x = front(snake_x);
	snake_tail_y = front(snake_y);
	scene[80*x + y] = ' ';
}

void snake_set_direction(int direction) {

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

static void snake_move() {

    /* Based on the snake direction, move head one coordinate*/
	int head_x = snake_head_x;
	int head_y = snake_head_y;

    switch(snake_direction) {
        /* UP and DOWN are y-axis roll-over 0-15 */
    case UP :
    	if (snake_direction != DOWN){
    		snake_enqueue(head_x, head_y-1);
    		snake_dequeue();
    	}
        break;
    case DOWN :
    	if (snake_direction != UP){
    		snake_enqueue(head_x, head_y+1);
    		snake_dequeue();
    	}
        break;
    case LEFT :
    	if (snake_direction != RIGHT){
    		snake_enqueue(head_x-1, head_y);
    		snake_dequeue();
    	}
        break;
    case RIGHT :
    	if (snake_direction != LEFT){
    		snake_enqueue(head_x+1, head_y);
    		snake_dequeue();
    	}
        break;
    default :
        break;
    }
}


