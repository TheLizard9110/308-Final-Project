//
//  main.c 
//  Final Project
//  Copyright (c) 2018 NoUMedia
//  hit f to pay royalties pl0x

#include <stdio.h>
#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#ifndef TEST
int main(int argc, const char * argv[]) {

	if(argc > 1) return 0;
	char size[1];
	int legalSize = 0;
	while(legalSize == 0){
		printf("%s\n","Choose your board size, (S)mall, (M)edium, or (L)arge");
		size[0] = fgetc(stdin);
		//fgetc works but not optimally, maybe change later

		//check for small
		if(0 == strcmp(size, "s") || 0 == strcmp(size, "S")){
			printf("%s\n", "Making Small board...");
			legalSize = 1;
			//makeBoard(5);
		}

		//check for medium
		else if(legalSize == 0 && (0 == strcmp(size, "m") || 0 == strcmp(size, "M"))){
                	printf("%s\n", "Making Medium board...");
                	legalSize = 1;
        	}

		//check for large
		else if(legalSize == 0 && (0 == strcmp(size, "l") || 0 == strcmp(size, "L"))){
                	printf("%s\n", "Making Large board...");
                	legalSize = 1;
        	}

		//else
		else{
			printf("%s\n", "That isn't a size, maybe try a differnet one.");
		}
	}//end while

	initscr();

	refresh();
	getch();

	endwin();




	//create and display board of proper size

	//printf("%s\n","im just looking for a better way to get up out of bed instead of getting on the internet and checking out who hit me up fam");

	
	return 0;
}
#endif
/*
void makeBoard(int s){
	int size = s;
	initscr();			
	printw("Hello World !!!");	
	refresh();			
	getch();			
	endwin();			
}*/



