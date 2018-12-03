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

int cols;
int rows;
int mines;
int highlightX = 1;
int highlightY = 1;

//#ifndef TEST
int main(int argc, const char * argv[]) {
	
	if(argc > 1) return 0;
	char size[1];
	int boardSize = 0;
	int legalSize = 0;
	//WINDOW *bWin = NULL;
	while(legalSize == 0){
		printf("%s\n","Choose your board size, (S)mall, (M)edium, or (L)arge");
		scanf("%s", size);
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
			mines = 15;
        	}

		//check for large
		else if(legalSize == 0 && (0 == strcmp(size, "l") || 0 == strcmp(size, "L"))){
                	printf("%s\n", "Making Large board...");
                	legalSize = 1;
			boardSize = 15;
			mines = 25;
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
	Board info = generate_mines();
	Board covered;
	covered.width = cols;
	covered.height = rows;
	int i, j;
        for(i = 0; i < rows; i++){
                for(j = 0; j < cols; j++){
                        covered.cboard[i][j] = "X";
                }
        }

	initscr();
        noecho();
        curs_set(FALSE);
        cbreak();
        printw("Minesweeper");
        print_board(covered);
        //printf("%s\n","im just looking for a better way to get up out of bed instead of getting on th$
        int input;
	const char * p;
        char buf[16];
	int infoTemp = 9;
        while(1){
                input = getch();
                switch(input){
                        case 'w':
                                if (highlightX > 1) highlightX--;
                                break;
                        case 's':
                                if (highlightX < rows) highlightX++;
                                break;
                        case 'a':
                                if (highlightY > 1) highlightY--;
                                break;
                        case 'd':
                                if (highlightY < cols) highlightY++;
                                break;
			case ' ':
				//sprintf(buf, "%d", info.board[highlightY-1][highlightX-1]);
				infoTemp = info.board[highlightY-1][highlightX-1];
				sprintf(buf, "%d", infoTemp);				
				//p = buf;
				//printf("%d", infoTemp);
				covered.cboard[highlightY-1][highlightX-1] = buf;
				break;
			case 'm':
			case 'M':
				if (covered.cboard[highlightY-1][highlightX-1] == "X"){
					covered.cboard[highlightY-1][highlightX-1] = "M";
				}
				else if (covered.cboard[highlightY-1][highlightX-1] == "M"){
					covered.cboard[highlightY-1][highlightX-1] = "X";
				}
				break;
                        default:
                                break;
                }
                print_board(covered);
                if (input == 'X' || input == 'x') break;
        }

	//bWin = newwin(rows + 2, 3 * cols + 2, 3, 8);
	//wborder(bWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		
	endwin();
	return 0;
}


void print_board(Board board) {
	int i;
        int j;
        int x = 0;
        int y = 2;
        /*
	for(i = 1; i <= rows; i++){
                for(j = 1; j <= cols; j++) {
                        if (highlightX == j && highlightY == i){
				attron(A_REVERSE);
				mvprintw(y, x, "X");
				attroff(A_REVERSE);
			}
			else{
				mvprintw(y, x, "X");
                        }
                        y += 2;
                }
		y = 2;
                x += 2;
		}*/
        //const char* p;
        //char buf[16];

        for(i = 1; i <= rows; i++){
                for(j = 1; j <= cols; j++){
                        //sprintf(buf, "%d", board.cboard[i-1][j-1]);
                        //p = buf;
			const char * q = board.cboard[i-1][j-1];
                        if (highlightX == j && highlightY == i){
				attron(A_REVERSE);
				mvprintw(y, x, q);
				attroff(A_REVERSE);
			}
			else{
				mvprintw(y, x, q);
			}
                        refresh();
                        y += 2;
                }
                y = 2;
                x += 2;
        }




	refresh();
}

Board generate_mines(){
	//initialize board with all 0's
	int i, j;
	int gb[rows][cols];
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++){
			gb[i][j] = 0;
		}
	}
	//printf("%d\n", gb[0][0]);
	//printf("%d\n", gb[4][4]);
	//insert mines randomly
	int a, b, c, d, x, y;
	
	for(i = 1; i <= mines; i++){
		a = rand_n(rows);
		b = rand_n(cols);
		//a, b = 1;
		if(gb[a][b] == 9) i--;
		else gb[a][b] = 9;
	}


	//count neighboring bombs

	Board info;
	info.width = cols;
	info.height = rows;

	for(a = 0; a < rows; a++)
		for(b = 0; b < cols; b++)
			if(gb[a][b] != 9){
				for(c = a - 1; c <= a + 1; c++)
					for(d = b - 1; d <= b + 1; d++)
						if (c < rows && d < cols && c >= 0 && d >= 0){
							if(gb[c][d] == 9)
								gb[a][b]++;
						}
			}


	//test population of the board
	/*
	x=0;
	y=2;
	const char* p;
	char buf[16];

	initscr();
	for(i = 1; i <= rows; i++){
		for(j = 1; j <= cols; j++){
			sprintf(buf, "%d", gb[i-1][j-1]);
			p = buf;
			mvprintw(y, x, p);
			refresh();
			y += 2;
		}
		y = 2;
		x += 2;
	}
	getch();
	endwin();
	*/



	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			info.board[i][j] = gb[i][j];

	return info;

}

int rand_n(int n) {
	return rand() % n + 1;
}

