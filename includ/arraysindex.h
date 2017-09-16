//
// Created by muhammad on 9/16/17.
//

#ifndef MAZEGENERATION_ARRAYSINDEX_H
#define MAZEGENERATION_ARRAYSINDEX_H

/**
     * @brief converting 2-D array to 1-D array
     * @param i is the row index.
     * @param j is the col index.
     * @return int with the required index in the 1-D  array
     */
int get_index(int i, int j, int rows, int cols);

/**
     * @brief return the top cell index in a converted array
     * @param i is the row index.
     * @param j is the col index.
     * @return int with the required index in the 1-D  array
     */
int get_up_index(int i, int j, int ROWS, int COLS);

/**
     * @brief return the right cell index in a converted array
     * @param i is the row index.
     * @param j is the col index.
     * @return int with the required index in the 1-D  array
     */

int get_right_index(int i, int j, int rows, int cols);


/**
     * @brief return the down cell index in a converted array
     * @param i is the row index.
     * @param j is the col index.
     * @return int with the required index in the 1-D  array
     */
int get_down_index(int i, int j, int rows, int cols);


/**
     * @brief return the left cell index in a converted array
     * @param i is the row index.
     * @param j is the col index.
     * @return int with the required index in the 1-D  array
     */
int get_left_index(int i, int j, int rows, int cols);

#endif //MAZEGENERATION_ARRAYSINDEX_H
