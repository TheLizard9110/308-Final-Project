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
#include <time.h>

int cols;
int rows;
int mines;
int highlightX = 1;
int highlightY = 1;
int winCount;
Bool loseBool;

//we tried real heccin hard to make this good
int main(int argc, const char * argv[]) {
	
	if(argc > 1){
		printf("%s\n", "No arguments required");
		return 0;
	}
	char size[1];
	srand(time(NULL));
	int boardSize = 0;
	int legalSize = 0;
	while(legalSize == 0){
		printf("%s\n","Choose your board size, (S)mall, (M)edium, or (L)arge");
		scanf("%s", size);

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
			printf("%s\n", "respects paid, thanks for the royalties");
		}

		//else
		else{
			printf("%s\n", "That isn't a size, maybe try a different one.");
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
        curs_set(0);
        cbreak();
        printw("Minesweeper: Press SPACE to reveal a cell and 'M' to flag a cell. Press 'X' to exit.");
        print_board(covered);
        //printf("%s\n","im just looking for a better way to get up out of bed instead of getting on the internet and checking out who's hit me up fam");
        int input;
	winCount = 0;
        char buf[16];
	loseBool = False;
	int infoTemp;
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
				reveal_cell(&covered, info, highlightX-1, highlightY-1);
				check_win(&covered, info);
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


	endwin();
	return 0;
}


void print_board(Board board) {
	int i;
        int j;
        int x = 0;
        int y = 2;

        for(i = 1; i <= rows; i++){
                for(j = 1; j <= cols; j++){
			const char * q = board.cboard[i-1][j-1];
                        if (highlightX == j && highlightY == i){
				attron(A_REVERSE);
				mvprintw(y, x, q); //highlight the selected cell
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
	//insert mines randomly
	int a, b, c, d, x, y;
	
	for(i = 0; i < mines; i++){
		a = RANDOM(rows);
		b = RANDOM(cols);
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
						if (c < rows && d < cols && c >= 0 && d >= 0){ //dont seg fault pls
							if(gb[c][d] == 9)
								gb[a][b]++;
						}
			}



	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			info.board[i][j] = gb[i][j];

	return info;

}

void reveal_cell(Board * covered, Board info, int x, int y){
	int infoTemp;
	if (covered->cboard[y][x] == "X" || covered->cboard[y][x] == "M")
		winCount++;
	infoTemp = info.board[y][x];
	if (infoTemp == 9){ //check if it's a mine
		covered->cboard[y][x] = "*";
		int numX = count_x(covered);
		if (numX > mines){
			winCount = (rows * cols - mines);
			loseBool = True;
		}
	}
	else if (infoTemp == 0){
		covered->cboard[y][x] = "0";
		for (int i = x-1; i <= x+1; i++){
			for (int j = y-1; j <= y+1; j++){
				if (i < rows && i >= 0 && j < cols && j >= 0 && (covered->cboard[j][i] == "X" || covered->cboard[j][i] == "M")){
					reveal_cell(covered, info, i, j); //recursively reveal cells surrounding the 0 cell
				}
			}
		}
	}
	else if (infoTemp == 1) covered->cboard[y][x] = "1";
	else if (infoTemp == 2) covered->cboard[y][x] = "2";
	else if (infoTemp == 3) covered->cboard[y][x] = "3";
	else if (infoTemp == 4) covered->cboard[y][x] = "4";
	else if (infoTemp == 5) covered->cboard[y][x] = "5";
	else if (infoTemp == 6) covered->cboard[y][x] = "6";
	else if (infoTemp == 7) covered->cboard[y][x] = "7";
	else if (infoTemp == 8) covered->cboard[y][x] = "8";
	else{
		covered->cboard[y][x] = "?"; //if we hit this case we dun goofed real bad
	}

}

void check_win(Board * covered, Board info){
	if (winCount >= (rows * cols - mines)){
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				reveal_cell(covered, info, i, j);
			}
		}
		if (loseBool) mvprintw(5, 5, "You hit a mine! Try again?"); //take a L
		else mvprintw(5, 5, "You Win!"); //get that W
	}
}

int count_x(Board * board){
	int count = 0;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (board->cboard[i][j] == "X" || board->cboard[i][j] == "M"){
				count++;
			}
		}
	}
	return count;
}


