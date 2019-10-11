#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char data[]="\
#####################\
#ooooooooo#ooooooooo#\
#o###o###o#o###o###o#\
#O# #o# #o#o# #o# #O#\
#o###o###o#o###o###o#\
#ooooooooooooooooooo#\
#o###o#o#####o#o###o#\
#o###o#o#####o#o###o#\
#ooooo#ooo#ooo#ooooo#\
#####o### # ###o#####\
    #o#   r   #o#    \
    #o# ##### #o#    \
#####o# #bpy# #o#####\
     o  #   #  o     \
#####o# ##### #o#####\
    #o#       #o#    \
    #o# ##### #o#    \
#####o# ##### #o#####\
#ooooooooo#ooooooooo#\
#o###o###o#o###o###o#\
#Ooo#ooooo@ooooo#ooO#\
###o#o#o#####o#o#o###\
###o#o#o#####o#o#o###\
#ooooo#ooo#ooo#ooooo#\
#o#######o#o#######o#\
#ooooooooooooooooooo#\
#####################";


#define MAZE_WIDTH 21
#define MAZE_HEIGHT 27
enum {
	CELL_TYPE_NONE,
	CELL_TYPE_WALL,
	CELL_TYPE_DOT,
	CELL_TYPE_POWER,
	CELL_TYPE_MAX
};
char cellAA[][2 + 1] = {
	"Å@",
	"Å°",
	"ÅE",
	"Åú",
};
int cells[MAZE_HEIGHT][MAZE_WIDTH];
enum {
	MONSTER_TYPE_PAC,
	MONSTER_TYPE_RED,
	MONSTER_TYPE_BLUE,
	MONSTER_TYPE_PINK,
	MONSTER_TYPE_PRANGE,
	MONSTER_TYPE_MAX
};
enum {
	DIRECTION_NORTH,
	DIRECTION_WEST,
	DIRECTION_SOUTH,
	DIRECTION_EAST,
	DIRECTION_MAX
};
int directions[][2] = {
{0, -1},//DIRECTION_NORTH,
{-1,0}, //DIRECTION_WEST
{0,1},  //DIRECTION_SOUTH
{1,0}   //DIRECTION_EAST
};
char monsterAA[][2 + 1] = {
	"Åó",
	"ê‘",
	"ê¬",
	"ìç",
	"ûÚ"
};
typedef struct {
	int x, y;
	int directions;
}MONSTER;
MONSTER monsters[MONSTER_TYPE_MAX ];
int getMonster(int _x, int _y) {
	for (int i = 0; i < MONSTER_TYPE_MAX; i++)
		if ((monsters[i].x == _x) && (monsters[i].y == _y))
			return i;
	return -1;
}
void display() {
	system("cls");
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			int monster = getMonster(x, y);
			if (monster >= 0)
				printf(monsterAA[monster]);
			else
				printf(cellAA[cells[y][x]]);
		}
		printf("\n");
	}
}
void gameOver() {
	monsters[MONSTER_TYPE_PAC].x = -1;
	monsters[MONSTER_TYPE_PAC].y = -1;
	display();
	printf("GAME OVER!!\a");
	_getch();
	exit(0);
}
int main() {
	srand((unsigned int)time(NULL));
	for (int y = 0; y < MAZE_HEIGHT; y++)
		for (int x = 0; x < MAZE_WIDTH; x++) {
			char c = data[MAZE_WIDTH * y + x];
			int cell = CELL_TYPE_NONE;
			switch (c) {
			case'#':cell = CELL_TYPE_WALL; break;
			case'o':cell = CELL_TYPE_DOT; break;
			case'O':cell = CELL_TYPE_POWER; break;
			default:
			{
				int monster = -1;
				switch (c) {
				case'@':monster = MONSTER_TYPE_PAC; break;
				case'r':monster = MONSTER_TYPE_RED; break;
				case'b':monster = MONSTER_TYPE_BLUE; break;
				case'p':monster = MONSTER_TYPE_PINK; break;
				case'y':monster = MONSTER_TYPE_PRANGE; break;
				}
				if (monster >= 0) {
					monsters[monster].x = x;
					monsters[monster].y = y;
				}
			}
			break;
		}
			cells[y][x] = cell;

	}
	while (1) {
		display();
		
		int x = monsters[MONSTER_TYPE_PAC].x;
		int y = monsters[MONSTER_TYPE_PAC].y;
		switch (_getch()) {
		case'w':y--; break;
		case's':y++; break;
		case'a':x--; break;
		case'd':x++; break;
		}
		x = (MAZE_WIDTH + x) % MAZE_WIDTH;
		if (getMonster(x, y) > MONSTER_TYPE_PAC) {
			gameOver();
		}
		if (cells[y][x] == CELL_TYPE_WALL) {

		}
		else {
			cells[y][x] =CELL_TYPE_NONE;
			monsters[MONSTER_TYPE_PAC].x = x;
			monsters[MONSTER_TYPE_PAC].y = y;
		}
		for (int i = MONSTER_TYPE_PAC + 1; i < MONSTER_TYPE_MAX; i++) {
			int x = monsters[i].x + directions[monsters[i].directions][0];
			int y = monsters[i].y + directions[monsters[i].directions][1];
			int monster = getMonster(x, y);
			if (monster == MONSTER_TYPE_PAC) {
				monsters[i].x = x;
				monsters[i].y = y;
				gameOver();
			}
			else if ((cells[y][x] == CELL_TYPE_WALL)
				|| (monster > MONSTER_TYPE_PAC)) {
				
				monsters[i].directions = rand() % DIRECTION_MAX;

			}
			else
				monsters[i].x = x;
				monsters[i].y = y;
		}
	}
}