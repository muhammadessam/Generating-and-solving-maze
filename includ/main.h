//
// Created by muhammad on 9/16/17.
//


#ifndef MAZEGENERATION_MAIN_H
#define MAZEGENERATION_MAIN_H

#include <stdio.h>
#include <spl/cslib.h>
#include <spl/gwindow.h>
#include <spl/gobjects.h>
#include <spl/stack.h>
#include "arraysindex.h"

#define WIDTH       400                         /**Maze width*/
#define HEIGHT      400                         /**Maze height*/
#define CELL_WIDTH   20                          /**Maze cell*/
#define ROWS        (HEIGHT/CELL_WIDTH)          /** number of maze rows*/
#define COLS        (WIDTH/CELL_WIDTH)           /** number of maze cols*/
#define START       0                           /** agent starting point*/
#define END         399                          /** agent ending point*/

/**
     * @brief struct holding each cell data
     */
struct cell {
    int i;
    int j;
    bool walls[4];
    bool visited;
    bool start;
};
/** new cell type */
typedef struct cell cell;


#endif //MAZEGENERATION_MAIN_H
