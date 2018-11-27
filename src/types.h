//
// types.h
// Final Project
//
// Copyright (c) 2018 NoUMedia
// yeet

#ifndef types_h
#define types_h

typedef enum { FALSE, TRUE } bool;

struct Cell{
    
};

typedef struct EmptyCell{
    Cell base;
    int count;
} EmptyCell;

typedef struct MineCell{
   Cell base;
} MineCell;

#endif /* types_h */
