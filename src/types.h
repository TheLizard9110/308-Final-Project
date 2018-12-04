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
#include <stdio.h>
#include <time.h>
#define MAX_WIDTH 15
#define MAX_HEIGHT 15
#define RANDOM(n) (rand() % n + 1)

typedef enum Bool { False, True } Bool;

typedef struct Cell{
    int count;
} Cell;

typedef struct CoveredCell{
    Cell base;
    char cover;
} EmptyCell;

typedef struct MineCell{
    Cell base;
    char mine;
} MineCell;


typedef struct
{
	int width;
	int height;
	Cell cells[MAX_WIDTH][MAX_HEIGHT];
	int board[MAX_WIDTH][MAX_HEIGHT];
	char * cboard[MAX_WIDTH][MAX_HEIGHT];
} Board;

//function sigs
void print_board(Board board);
Board generate_mines();
int rand_n(int n);
void reveal_cell(Board * covered, Board info, int x, int y);
void check_win(Board * covered, Board info);
int count_x(Board * board);

#endif /* types_h */
