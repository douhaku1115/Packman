#include <conio.h>
#include <stdio.h>

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

int main() {
	for (int y = 0; y < MAZE_HEIGHT; y++)
		for (int x = 0; x < MAZE_WIDTH; x++) {
			char c = data[MAZE_WIDTH * y + x];
			int cell = CELL_TYPE_NONE;
			switch (c) {
			case'#':cell = CELL_TYPE_WALL; break;
			case'o':cell = CELL_TYPE_DOT; break;
			case'O':cell = CELL_TYPE_POWER; break;
		}
			cells[y][x] = cell;

	}

	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			printf(cellAA[cells[y][x]]);
		}
		printf("\n");
	}
	_getch();

}