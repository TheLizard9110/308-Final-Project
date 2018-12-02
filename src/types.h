//
// types.h
// Final Project
//
// Copyright (c) 2018 NoUMedia
// yeet

#ifndef types_h
#define types_h
#include <curses.h>
#include <panel.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WIDTH 15
#define MAX_HEIGHT 15
#define FALSE 0
#define TRUE 1

typedef struct Cell{
    
} Cell;

typedef struct EmptyCell{
    Cell base;
    int count;
} EmptyCell;

typedef struct MineCell{
   Cell base;
} MineCell;


typedef struct Board
{
	int width;
	int height;
	int board[MAX_WIDTH][MAX_HEIGHT];
} Board;

//function sigs
void print_board(int r, int c, int m);
Board generate_mines(Board b, int m);


#endif /* types_h */
