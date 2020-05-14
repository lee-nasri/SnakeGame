#include "snake.h"
#include "queue.c"

struct Queue* snake_x = createQueue(1000);
struct Queue* snake_y = createQueue(1000);
static volatile int snake_direction = RIGHT; /* Direction snake should move next */
static volatile int score; /* Current score of game */
static int *snake_head_x;
static int *snake_head_y;
static int *snake_tail_x;
static int *snake_tail_y;


void snake_init(){
	for (int i = 0; i < 5; ++i) { snake_enqueue(0, i); }
	snake_head_x = rear(snake_x);
	snake_head_y = rear(snake_y);
	snake_tail_x = front(snake_x);
	snake_tail_y = front(snake_y);
}

void snake_enqueue(int x, int y, char scene[1920]){
	enqueue(snake_x, x);
	enqueue(snake_y, y);
	snake_head_x = rear(snake_x);
	snake_head_y = rear(snake_y);
	scene[80*x + y] = '@';
}

void snake_dequeue(char scene[1920]){
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

void snake_move(char scene[1920]) {

    /* Based on the snake direction, move head one coordinate*/
	int head_x = snake_head_x;
	int head_y = snake_head_y;

    switch(snake_direction) {
        /* UP and DOWN are y-axis roll-over 0-15 */
    case UP :
    	if (snake_direction != DOWN){
    		snake_enqueue(head_x, head_y-1, scene[1920]);
    		snake_dequeue(scene[1920]);
    	}
        break;
    case DOWN :
    	if (snake_direction != UP){
    		snake_enqueue(head_x, head_y+1, scene[1920]);
    		snake_dequeue(scene[1920]);
    	}
        break;
    case LEFT :
    	if (snake_direction != RIGHT){
    		snake_enqueue(head_x-1, head_y, scene[1920]);
    		snake_dequeue(scene[1920]);
    	}
        break;
    case RIGHT :
    	if (snake_direction != LEFT){
    		snake_enqueue(head_x+1, head_y, scene[1920]);
    		snake_dequeue(scene[1920]);
    	}
        break;
    default :
        break;
    }
}


