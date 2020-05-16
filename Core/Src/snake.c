#include "snake.h"
#include "queue.h"

struct Queue* snake_x;
struct Queue* snake_y;
struct Queue* enemy_1_x;
struct Queue* enemy_1_y;
struct Queue* enemy_2_x;
struct Queue* enemy_2_y;
static volatile int snake_direction;
static volatile int enemy_1_direction;
static volatile int enemy_2_direction;
static volatile int score; /* Current score of game */
static int snake_head_x;
static int snake_head_y;
static int snake_tail_x;
static int snake_tail_y;
static int food_constant;
static int food_time;
static int obstacle_constant;
static int obstacle_time;
static int isPlay;
static int level;
static int level_constant;


void snake_init(char scene[1920]){
	/* Initiate my snake */
	snake_x = createQueue(300); snake_y = createQueue(300);
	snake_direction = RIGHT;
	for (int x = 0; x < 5; ++x) { snake_enqueue(x, 0, scene); }
	snake_head_x = rear(snake_x); snake_head_y = rear(snake_y);
	snake_tail_x = front(snake_x); snake_tail_y = front(snake_y);

	/* Initiate enemy */
	enemy_1_x = createQueue(300); enemy_1_y = createQueue(300);
	enemy_2_x = createQueue(300); enemy_2_y = createQueue(300);
	enemy_1_direction = RIGHT;
	enemy_2_direction = LEFT;
	/* Initiate game constant */
	scene_setScore(scene);
	scene_setLevel(scene);
	score = 0; food_time = 0; food_constant = 20; isPlay = 1;
	obstacle_time = 0; obstacle_constant = 20;
	level = 1; scene_setLevel(scene); level_constant = 60;
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

void scene_setScore(char scene[1920]){
	scene[80*22 + 0] = 'S';
	scene[80*22 + 1] = 'c';
	scene[80*22 + 2] = 'o';
	scene[80*22 + 3] = 'r';
	scene[80*22 + 4] = 'e';
	scene[80*22 + 6] = ':';
	int i1 = score%10;
	int i2 = (score%100) / 10;
	int i3 = (score%1000) / 100;
	if (score < 0) snake_gameOver(scene);

	scene[80*22 + 10] = intTOchar(i1);
	scene[80*22 + 9] = intTOchar(i2);
	scene[80*22 + 8] = intTOchar(i3);
}

void snake_setDirection(int direction) {
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
	int foodScore;

    switch(snake_direction) {
    case UP :
    	foodScore = snake_foodScore(head_x, head_y - 1, scene);
    	snake_enqueue(head_x, head_y - 1, scene);
    	if ( foodScore == 0 )  snake_dequeue(scene);
    	else if ( foodScore == -99 ) snake_gameOver(scene);
    	else snake_feed(foodScore, scene);
        break;
    case DOWN :
    	foodScore = snake_foodScore(head_x, head_y + 1, scene);
    	snake_enqueue(head_x, head_y+1, scene);
    	if ( foodScore == 0 )  snake_dequeue(scene);
    	else if ( foodScore == -99 ) snake_gameOver(scene);
    	else snake_feed(foodScore, scene);
        break;
    case LEFT :
    	foodScore = snake_foodScore(head_x - 1, head_y, scene);
    	snake_enqueue(head_x-1, head_y, scene);
    	if ( foodScore == 0 )  snake_dequeue(scene);
    	else if ( foodScore == -99 ) snake_gameOver(scene);
    	else snake_feed(foodScore, scene);
        break;
    case RIGHT :
    	foodScore = snake_foodScore(head_x + 1, head_y, scene);
    	snake_enqueue(head_x+1, head_y, scene);
    	if ( foodScore == 0 )  snake_dequeue(scene);
    	else if ( foodScore == -99 ) snake_gameOver(scene);
    	else snake_feed(foodScore, scene);
        break;
    default :
        break;
    }
}

int snake_foodScore(int x, int y, char scene[1920]){
	/* This function checks what the next pixel is ?
	 * if next pixel is food. return score of that food
	 * if next pixel is snake. return -1 -> game over
	 * else return 0 mean next pixel is free space.
	 */
	if ( scene[80 * y + x] == 'O' ) return 1;
	else if ( scene[80 * y + x] == '#'  ) return -1;
	else if ( scene[80 * y + x] == '@' ) return -99;
	return 0;
}

void snake_feed(int foodScore, char scene[1920]){
	score += foodScore;
	scene_setScore(scene);
}

void snake_newFood(char scene[1920]){
	if ( isPlay == 1) {
		food_time ++;
		int x = rand() % 80;
		int y = rand() % 24;
		if ( (scene[80 * y + x] == ' ' || scene[80 * y + x] == '#') && food_time % food_constant == 0) scene[80 * y + x] = 'O';
	}
}

void snake_newObstacle(char scene[1920]){
	if ( isPlay == 1) {
		obstacle_time ++;
		int x = rand() % 80;
		int y = rand() % 24;
		if ( scene[80 * y + x] == ' ' && obstacle_time % obstacle_constant == 0) scene[80 * y + x] = '#';
	}
}

void snake_gameOver(char scene[1920]){
	while ( !isEmpty( snake_x) )  { snake_dequeue(scene); }
	scene_setPixelX(35, 44, 10, scene, "Game  Over", 10);
	scene_setPixelX(28, 52, 11, scene, "Press 'K' to start again.", 25);
}

void snake_levelUp(int timeX, char scene[1920]){
	if (level == 1 && timeX % 50 == 0) { obstacle_constant = 50; level++; scene_setLevel(scene); }
	else if (level == 2 && timeX % 150 == 0) { obstacle_constant = 40; level++; scene_setLevel(scene); }
	else if (level == 3 && timeX % 300 == 0) { obstacle_constant = 30; level++; scene_setLevel(scene); }
	else if (level == 4 && timeX % 600 == 0) { obstacle_constant = 20; level++; scene_setLevel(scene); }
	else if (level == 5 && timeX % 1200 == 0) { obstacle_constant = 10; level++; scene_setLevel(scene); }
}

void scene_setLevel(char scene[1920]){
	scene_setPixelX(0, 7, 23, scene, "level : ", 8);
	scene[80 * 23 + 8] = intTOchar(level);
}


void scene_setPixelX(int x1, int x2, int y, char scene[1920], char text[], int size){
	if (x1 > x2) { scene_setPixelX(x2, x1, y, scene, text, size); }
	else {
		int indeX = 0;
		for (int i=x1; i<=x2; i++) { scene[80 * y + i] = text[indeX];
		indeX++;
		if (indeX >= size) return ;
		}
	}
}

void scene_setPixelY(int x, int y1, int y2, char scene[1920], char text[], int size){
	if (y1 > y2) { scene_setPixelX(x, y1, y2, scene, text, size); }
	else {
		int indeX = 0;
		for (int i=y1; i<=y2; i++) { scene[80 * i + x] = text[indeX];
		indeX++;
		if (indeX >= size) return ;
		}
	}
}

void scene_mainmenu(char scene[1920]){
	/* For observing the beginning of a pixel */
	scene_setPixelX(0, 4, 0, scene, "START", 5);
	scene_setPixelX(36, 44, 10, scene, "SNAKE  GO", 9);
	scene_setPixelX(25, 52, 11, scene, "Press 'K' to start the game.", 28);
	scene_setPixelX(0, 79, 0, scene, "________________________________________________________________________________", 80);
	scene_setPixelX(0, 79, 22, scene, "________________________________________________________________________________", 80);
	scene_setPixelY(0, 1, 22, scene, "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||", 80);
	scene_setPixelY(79, 1, 22, scene, "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||", 80);
	isPlay = 0;
}

void scene_clear(char scene[1920]){
	for(int i=0;i<1920; i++) scene[i] = ' ';
	isPlay = 0;
}

char intTOchar(int integers){
	if (integers == 1) return '1';
	else if (integers == 2) return '2';
	else if (integers == 3) return '3';
	else if (integers == 4) return '4';
	else if (integers == 5) return '5';
	else if (integers == 6) return '6';
	else if (integers == 7) return '7';
	else if (integers == 8) return '8';
	else if (integers == 9) return '9';
	else return '0';
}


