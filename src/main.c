//
//  main.c 
//  Final Project
//  Copyright (c) 2018 NoUMedia
//  hit f to pay royalties pl0x

//gcc main.c -o game -lncurses

#include <stdio.h>
#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <panel.h>

//#ifndef TEST
int main(int argc, const char * argv[]) {
	int rows;
	int cols;
	int bombs;
	if(argc > 1) return 0;
	char size[1];
	int boardSize = 0;
	int legalSize = 0;
	//WINDOW *bWin = NULL;
	while(legalSize == 0){
		printf("%s\n","Choose your board size, (S)mall, (M)edium, or (L)arge");
		size[0] = fgetc(stdin);
		//fgetc works but not optimally, maybe change later

		//check for small
		if(0 == strcmp(size, "s") || 0 == strcmp(size, "S")){
			printf("%s\n", "Making Small board...");
			legalSize = 1;
			boardSize = 5;
			mines = 4;
		}

		//check for medium
		else if(legalSize == 0 && (0 == strcmp(size, "m") || 0 == strcmp(size, "M"))){
                	printf("%s\n", "Making Medium board...");
                	legalSize = 1;
			boardSize = 10;
			mines = 13;
        	}

		//check for large
		else if(legalSize == 0 && (0 == strcmp(size, "l") || 0 == strcmp(size, "L"))){
                	printf("%s\n", "Making Large board...");
                	legalSize = 1;
			boardSize = 15;
			mines = 20;
        	}
		
		//check respects
		else if(legalSize == 0 && (0 == strcmp(size,"f") || 0 == strcmp(size, "F"))){
			printf("%s\n", "respects paid, thank you for your service");
		}

		//else
		else{
			printf("%s\n", "That isn't a size, maybe try a differnet one.");
		}
	}//end while

	rows = boardSize;
	cols = boardSize;


	//bWin = newwin(rows + 2, 3 * cols + 2, 3, 8);
	//wborder(bWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

	print_board(rows, cols, bombs);
	//printf("%s\n","im just looking for a better way to get up out of bed instead of getting on the internet and checking out who hit me up fam");

	
	return 0;
}


void print_board(int r, int c, int m) {
	int i;
        int j;
        int x = 0;
        int y = 2;
	int mines = m;
	int rows = r;
	int cols = c;
	Board newBoard;
	newBoard->width = cols;
	newBoard->height = rows;
        initscr();
        noecho();
        curs_set(FALSE);
	printw("Minesweeper");
        for(i = 1; i <= rows; i++){
                for(j = 1; j <= cols; j++) {
                        mvprintw(y, x, "X");
                        refresh();
                        y += 2;
                }
		y = 2;
                x += 2;
        }


	refresh();
	getch();
	endwin();
}

Board generate_mines(Board b, int m){
	int a;
	int b;
	int mines = m;
	int i;
	for(i = 1; i <= mines; i++){
		
	}
}


