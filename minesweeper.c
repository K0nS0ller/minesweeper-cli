#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROW 9
#define COLUMN 9

struct block {
	bool mine;
	int mines_around;
	bool opened;
	bool flag;
};

struct block grid[ROW][COLUMN];

void sleep(float seconds){
	time_t start_time = time(NULL);
	time_t finish_time;
	do {
		finish_time = time(NULL);
	} while(finish_time - start_time < seconds);
}

int rand_sub;

int randnum(){
	srand(time(NULL) + rand_sub);
	int randNum = rand() % 101;
	return randNum;
}

int flags;
int game_status;
int bomb_count;

void begin(){
	flags == 0;
	for(int r = 1; r != 10; r++){
		for(int c = 1; c != 10; c++){
			grid[r][c].mines_around = 0;
			grid[r][c].opened = false;
			grid[r][c].mine = false;
		}
	}

	for(int r = 1; r < 10; r++){
		for(int c = 1; c < 10; c++){
			if(randnum() % 101 < 1){
				grid[r][c].mine = true;
				bomb_count++;
			}
			rand_sub++;

		}
	}
}


void field_print(){
	system("clear");
	printf("legend:\n # - not opened\t 1,2,3 ... - opened, how much bombs around\n * - bomb(game over:)))\t F - flag\n Flags used: %d \nbombs: %d\n", flags, bomb_count);
	if(game_status == 0){
		for (int columns = 1; columns < 10; columns++){
			for (int rows = 1; rows < 10; rows++){
				if(grid[rows][columns].flag){
					printf(" F ");
				} else{
					if(grid[rows][columns].opened){
						if(grid[rows][columns].mines_around > 0){
							printf(" %d ", grid[rows][columns].mines_around);
						} else{
							printf("   ");
						}

					} else{
						printf(" # ");
					}
				}
			}
			printf("\n\n");
		}
	} else{
		if(game_status == 1){
			for (int columns = 1; columns < 10; columns++){
				for (int rows = 1; rows < 10; rows++){
					if(grid[rows][columns].mine){
						printf(" * ");
					} else{
						if(grid[rows][columns].mines_around > 0){
							printf(" %d ", grid[rows][columns].mines_around);
						} else{
							printf("   ");
						}
					}
				}
				printf("\n\n");
			}
			printf("game over.\n");
		}
	}
}

void check_around(){
	int mines;
	for(int row = 1; row < 10; row++){
		for(int column = 1; column < 10; column++){
			int r_around = row - 1;
			int c_around = column -1;
			void check(){
				if(r_around < 10 && r_around > 0 && c_around < 10 && c_around > 0){
					if(grid[r_around][c_around].mine){
						grid[row][column].mines_around++;
					}
				}
			}
			for(r_around; r_around != row + 1; r_around++){
				check();
			}
			for(c_around; c_around != column + 1; c_around++){
				check();
			}
			for(r_around; r_around != row - 1; r_around--){
				check();
			}
			for(c_around; c_around != column - 1; c_around--){
				check();
			}
		}
	}
}




void logic(){
	field_print();
	int row;
	int column;
	int todo;
	printf("\nchoose row (1-9) : ");
	scanf("%d", &row);
	printf("\nchoose column: ");
	scanf("%d", &column);
	if(row > 9 || row < 1 || column > 9 || column < 1){
		printf("bad coordinates. try again\n");
		logic();
	}
	printf("\nwhat to do (0 - change another block; 1 - open, 2 - set flag, 3 - unset flag):");
	scanf("%d",&todo);
	printf("\n");
	if(todo < 0 || todo > 3){
		printf("bad interaction. Try again\n");
		logic();
	}
	if(todo == 1){
		if(grid[row][column].mine == true && grid[row][column].flag == false){
			game_status = 1;
			field_print();
		} else{
			if(grid[row][column].flag){
				printf("there's flag. Can't be opened\n");
			} else{
				grid[row][column].opened = true;
				if(grid[row][column].mine = false && grid[row][column].flag == false){
					int r_around = row - 1;
					int c_around = column -1;
					for(r_around; r_around != row + 1; r_around++){
						if(grid[r_around][c_around].flag == false){
							grid[r_around][c_around].opened = true;
						}
					}
					for(c_around; c_around != column + 1; c_around++){
						if(grid[r_around][c_around].flag == false){
							grid[r_around][c_around].opened = true;
						}
					}
					for(r_around; r_around != row - 1; r_around--){
						if(grid[r_around][c_around].flag == false){
							grid[r_around][c_around].opened = true;
						}
					}
					for(c_around; c_around != column - 1; c_around--){
						if(grid[r_around][c_around].flag == false){
							grid[r_around][c_around].opened = true;
						}
					}
				}
			}
		}
		if(game_status == 0){
			logic();
		}
	}
	if(todo == 0){
		logic();
	}
	if(todo == 2){
		if (grid[row][column].flag == false && grid[row][column].opened == false){
			grid[row][column].flag = true;
			printf("flag set!\n");
			flags++;
			bomb_count -= 1;
			if(bomb_count = 0){
				printf("you win!!");
				exit;
			}else{
				logic();
			}
		}
	}
	if(todo == 3){
		if (grid[row][column].flag){
			grid[row][column].flag = false;
			printf("flag unset!\n");
			flags--;
		}
		logic();
	}
}


int main() {
	printf("          m                                                                  \n mmmmm  mmm    m mm    mmm    mmm  m     m  mmm    mmm   mmmm    mmm    m mm \n # # #    #    #   #  #   #  #      m m m  #   #  #   #  #   #  #   #   #   m\n # # #    #    #   #  #***   ***m   #m#m#  #****  #****  #   #  #****   #  \n # # #  mm#mm  #   #  *#mm*  *mmm*   # #   *#mm*  *#mm*  ##m#*  *#mm*   #    \n                                                         #\n                                                         #\n");
	begin();
	check_around();
	logic();
	return 0;
}
