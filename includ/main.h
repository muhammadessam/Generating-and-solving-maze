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

#define WIDTH       400                                /**Maze width*/
#define HEIGHT      400                                /**Maze height*/
#define CELL_WIDTH   40                                /**Maze cell*/
#define ROWS        (HEIGHT/CELL_WIDTH)                /** number of maze rows*/
#define COLS        (WIDTH/CELL_WIDTH)                /** number of maze cols*/
#define START       0                                 /** agent starting point*/
#define END         99                                /** agent ending point*/
/**
     * @brief struct holding each cell data
     */
struct cell {
    int i;
    int j;
    bool walls[4];
    bool visited;
};
/** new cell type */
typedef struct cell cell;

/**
     * @brief a function for init an array of cells with default parameters
     * \brief each with its location i, j, and have all walls as closed, and not visited
     * @param grid[ROW*COLS] a 1-D array holding all the cells in the grid.
     *
     */
void init_grid(cell grid[ROWS * COLS]);

/// \brief used in the maze genration phase for drawing a single cell with walls opend or closed
/// \param cell cell with it's info to be drawed
/// \param panel  Gwindow object to draw in
void draw_cell(cell *cell, GWindow panel);

/**
 * @brief function to show which cell is being modified right now in the generation phase
 * @param current a pointer to the current cell
 * @param panel a GWindow struct to draw in
 */
void draw_current_cell(cell *current, GWindow panel);

/**
 * gettig unvisited neighbors
 * @param cell1 current cell
 * @param grid  array of cells
 * @return index of the unvisited neighbor
 */
int get_next_unvisited_neighbor(cell *cell1, cell *grid);

/**
 * removing wall from a cell to get a perfect maze
 * @param current current cell
 * @param next  next unvisited cell
 */
void remove_walls(cell *current, cell *next);

int move_up(int i, int j, int rows, int cols);

int move_right(int i, int j, int rows, int cols);

int move_down(int i, int j, int rows, int cols);

int move_left(int i, int j, int rows, int cols);
/**
 * meaning of full closed is that all the walls of the current cell and neighboring cells are all closed
 * @param cell1 current cell
 * @param grid  array of all he cells to check neighbours
 * @return true if #of opening walls is zero otherwise false
 */
bool is_full_closed(cell *cell1, cell grid[COLS*ROWS]);

/**
 * meaning of a half closed is that at least on wall of the current cell and neighboring cell is open
 * @param cell1 current cell
 * @param grid  array of all he cells to check neighbours
 * @return
 */
int is_half_closed(cell *cell1,cell grid[ROWS*COLS]);

/**
 * moving the robot to solve the maze
 * @param cell1 current cell
 * @param grid  array of all the cells
 * @param movedCells stack to store the move to cells
 * @param moves a stack to stor the moves it self meaning up right left down
 * @param panel panel to draw the move
 * @return a pointer to the next cell
 */
cell* move_agent(cell *cell1, cell grid[ROWS*COLS], Stack movedCells, Stack moves, GWindow panel);

/**
 * dummy fnction used to draw moves of solution
 * @param temp pointer to the current cell
 * @param panel panel to draw in
 */
void draw_for_solution(cell *temp, GWindow panel);
#endif //MAZEGENERATION_MAIN_H
