//
// Created by muhammad on 9/16/17.
//
#include "../includ/arraysindex.h"

int get_index(int i, int j, int rows, int cols) {
    if (i < 0 || j < 0 || i > rows - 1 || j > cols - 1)
        return -1;
    else
        return j + i * cols;
}

int get_up_index(int i, int j, int rows, int cols) {

    return get_index(i - 1, j,rows, cols);
}

int get_right_index(int i, int j, int rows, int cols) {
    return get_index(i, j + 1, rows, cols);
}

int get_down_index(int i, int j, int rows, int cols) {
    return get_index(i + 1, j, rows, cols);
}

int get_left_index(int i, int j, int rows, int cols) {
    return get_index(i, j - 1, rows, cols);
}