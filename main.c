/**
 * @author: Muhammad Essam
 * @Job: student at faculty of engineering minia university
 * @date: 9/16/2017
 */

#include "includ/main.h"

int main() {
    srand(9);
    /**
     * maze generetion
     */
    cell grid[ROWS * COLS];
    GWindow panel = newGWindow(WIDTH, HEIGHT);
    cell* current = NULL;
    Stack Generation_phase_visited_cells = newStack();
    init_grid(grid);
    for (int i = 0; i < COLS * ROWS; ++i) {
        draw_cell(&grid[i],panel);
    }
    grid[START1].visited = true;
    current = &grid[START1];
    push(Generation_phase_visited_cells, current);
    while (!isEmpty(Generation_phase_visited_cells)) {
        int c;
        if ((c = get_next_unvisited_neighbor(current, grid)) != -1) {
            // STEP 1 mark as visited
            grid[c].visited = true;
            // push it to the stack
            push(Generation_phase_visited_cells, current);
            //STEP 3 remove walls
            remove_walls(current, &grid[c]);
            // sTEP 4
            current = &grid[c];
        } else if (!isEmpty(Generation_phase_visited_cells)) {
            current = pop(Generation_phase_visited_cells);
        }

        draw_current_cell(current,panel);
        //pause(2);
        draw_cell(current,panel);

    }

    for (int j = 0; j < ROWS * COLS; ++j) {
        grid[j].visited = false;
    }

    /**
     * maze solution
     */
    srand(2);
    agent ag1 = {NULL, newStack(),newStack(), 0};
    agent ag2 = {NULL, newStack(), newStack(), 1};
    ag1.current = &grid[START1];
    ag2.current = &grid[START2];
    while (1) {
        draw_agent(ag1, panel);
        printf("ag1: ");
        ag1.current = move_agent(ag1,grid,panel);
        draw_agent(ag2, panel);
        printf("ag2: ");
        ag2.current= move_agent(ag2, grid,panel);
        if (ag1.current == NULL || ag2.current==NULL)
            break;
        pause(500);
    }
    return 0;
}

void init_grid(cell grid[ROWS * COLS]) {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cell temp = {i, j, {true, true, true, true}, false};
            grid[get_index(i, j, ROWS, COLS)] = temp;
        }
    }
}

void draw_cell(cell *cell, GWindow panel) {
    int x = cell->j * CELL_WIDTH;
    int y = cell->i * CELL_WIDTH;

    if (cell->visited) {
        GRect temp = newGRect(x, y, CELL_WIDTH, CELL_WIDTH);
        setFillColor(temp, "WHITE");
        setFilled(temp, true);
        add(panel, temp);
    }
    GLine line_top = newGLine(x, y, x + CELL_WIDTH, y);
    GLine liner_ight = newGLine(x + CELL_WIDTH, y, x + CELL_WIDTH, y + CELL_WIDTH);
    GLine line_down = newGLine(x + CELL_WIDTH, y + CELL_WIDTH, x, y + CELL_WIDTH);
    GLine line_left = newGLine(x, y + CELL_WIDTH, x, y);

    if (cell->walls[0]) {
        setColor(line_top, "BLACK");
        add(panel, line_top);
    } else {
        setColor(line_top, "WHITE");
        add(panel, line_top);
    }
    if (cell->walls[1]) {
        setColor(liner_ight, "BLACK");
        add(panel, liner_ight);
    } else {
        setColor(liner_ight, "WHITE");
        add(panel, liner_ight);
    }
    if (cell->walls[2]) {
        setColor(line_down, "BLACK");
        add(panel, line_down);
    } else {
        setColor(line_down, "WHITE");
        add(panel, line_down);
    }
    if (cell->walls[3]) {
        setColor(line_left, "BLACK");
        add(panel, line_left);
    } else {
        setColor(line_left, "WHITE");
        add(panel, line_left);
    }


}

void draw_current_cell(cell *current, GWindow panel) {
    int x = current->j * CELL_WIDTH;
    int y = current->i * CELL_WIDTH;
    GRect temp = newGRect(x, y, CELL_WIDTH, CELL_WIDTH);
    setFillColor(temp, "RED");
    setFilled(temp, true);
    add(panel, temp);
}

int get_next_unvisited_neighbor(cell *cell1, cell *grid) {
    int picked;
    bool arr[4] = {false, false, false, false};
    int top = get_index(cell1->i - 1, cell1->j,ROWS, COLS);
    int right = get_index(cell1->i, cell1->j + 1, ROWS, COLS);
    int down = get_index(cell1->i + 1, cell1->j, ROWS, COLS);
    int left = get_index(cell1->i, cell1->j - 1, ROWS, COLS);
    int arr_values[4] = {top, right, down, left};
    if ((top != -1))
        if (!grid[top].visited)
            arr[0] = true;
    if ((right != -1))
        if (!grid[right].visited)
            arr[1] = true;
    if ((down != -1))
        if (!grid[down].visited)
            arr[2] = true;
    if ((left != -1))
        if (!grid[left].visited)
            arr[3] = true;
    int i = 0;
    for (i = 0; i < 4; i++) {
        if (arr[i] == true)
            break;
    }
    if (i == 4)
        return -1;
    picked = rand() % 4;
    while (!arr[picked]) {
        picked = rand() % 4;
    }
    return arr_values[picked];
}

void remove_walls(cell *current, cell *next) {
    int x = current->i - next->i;
    if (x == 1) {
        current->walls[0] = false;
        next->walls[2] = false;
    } else if (x == -1) {
        current->walls[2] = false;
        next->walls[0] = false;
    }
    int y = current->j - next->j;
    if (y == 1) {
        current->walls[3] = false;
        next->walls[1] = false;

    } else if (y == -1) {
        current->walls[1] = false;
        next->walls[3] = false;
    }
}

int move_up(int i, int j, int rows, int cols) {
    printf("moving top\n");
    return get_index(i - 1, j, rows, cols);
}

int move_right(int i, int j, int rows, int cols) {
    printf("moving right\n");
    return get_index(i, j + 1, rows, cols);
}

int move_down(int i, int j, int rows, int cols) {
    printf("moving down\n");
    return get_index(i + 1, j, rows, cols);
}

int move_left(int i, int j, int rows, int cols) {
    printf("moving left\n");
    return get_index(i, j - 1, rows, cols);
}

bool is_full_closed(cell *cell1, cell grid[COLS*ROWS]) {
    bool top = false, right = false, down = false, left = false;
    if (get_up_index(cell1->i, cell1->j,ROWS, COLS) != -1) {
        if ((cell1->walls[0]) && (grid[get_up_index(cell1->i, cell1->j, ROWS, COLS)].walls[2])) {
            top = true;
        }
    } else {
        top = true;
    }
    if (get_right_index(cell1->i, cell1->j, ROWS, COLS) != -1) {
        if ((cell1->walls[1]) && (grid[get_right_index(cell1->i, cell1->j, ROWS, COLS)].walls[3])) {
            right = true;
        }
    } else {
        right = true;
    }
    if (get_down_index(cell1->i, cell1->j, ROWS, COLS) != -1) {
        if ((cell1->walls[2]) && (grid[get_down_index(cell1->i, cell1->j, ROWS, COLS)].walls[0])) {
            down = true;
        }
    } else {
        down = true;
    }
    if (get_left_index(cell1->i, cell1->j, ROWS, COLS) != -1) {
        if ((cell1->walls[3]) && (grid[get_left_index(cell1->i, cell1->j, ROWS, COLS)].walls[1])) {
            left = true;
        }
    } else {
        left = true;
    }

    if (top && left && right && down)
        return true;
    else
        return false;

}

int is_half_closed(cell *cell1,cell grid[ROWS*COLS]) {
    bool top = false, right = false, down = false, left = false;
    if (get_up_index(cell1->i, cell1->j, ROWS, COLS) != -1) {
        if ((cell1->walls[0]) && (grid[get_up_index(cell1->i, cell1->j, ROWS, COLS)].walls[2])) {
            top = true;
        }
    } else {
        top = true;
    }
    if (get_right_index(cell1->i, cell1->j, ROWS, COLS) != -1) {
        if ((cell1->walls[1]) && (grid[get_right_index(cell1->i, cell1->j, ROWS, COLS)].walls[3])) {
            right = true;
        }
    } else {
        right = true;
    }
    if (get_down_index(cell1->i, cell1->j, ROWS, COLS) != -1) {
        if ((cell1->walls[2]) && (grid[get_down_index(cell1->i, cell1->j, ROWS, COLS)].walls[0])) {
            down = true;
        }
    } else {
        down = true;
    }
    if (get_left_index(cell1->i, cell1->j, ROWS, COLS) != -1) {
        if ((cell1->walls[3]) && (grid[get_left_index(cell1->i, cell1->j, ROWS, COLS)].walls[1])) {
            left = true;
        }
    } else {
        left = true;
    }
    if (!top) {
        return 0;
    } else if (!right) {
        return 1;
    } else if (!down) {
        return 2;
    } else if (!left) {
        return 3;
    } else {
        return -1;
    }
}

cell *move_agent(agent ag, cell grid[ROWS*COLS], GWindow panel) {
    if (get_index(ag.current->i, ag.current->j, ROWS, COLS) == (END1)) {
        printf("you have reached\n");
        return NULL;
    }
    bool trapped = false;
    ag.current->visited = true;
    ag.current->visited_by_which_agent = ag.id;
    int number_of_opened_walls = 0;
    int move_from = 0;
    for (int i = 0; i < 4; i++) {
        if (!ag.current->walls[i])
            number_of_opened_walls++;
    }
    if (number_of_opened_walls == 1) {
        ///////////* getting which wall is opened*//////////////////////////////
        for (int i = 0; i < 4; i++) {
            if (!ag.current->walls[i]) {
                move_from = i;
                break;
            }
        }
        ////////////////////////////////* setting the move *////////////////////////
        if (move_from == 0) {
            if (!grid[get_up_index(ag.current->i, ag.current->j, ROWS, COLS)].visited) {
                push(ag.moved_cells, ag.current);
                push(ag.moves, "top");
                ag.current->walls[move_from] = true;
                grid[get_up_index(ag.current->i, ag.current->j, ROWS, COLS)].walls[2] = true;
                return (&grid[move_up(ag.current->i, ag.current->j, ROWS, COLS)]);
            }else{
                trapped = true;
            }
        } else if (move_from == 1) {
            if (!grid[get_right_index(ag.current->i, ag.current->j, ROWS, COLS)].visited) {
                push(ag.moved_cells, ag.current);
                push(ag.moves, "right");
                ag.current->walls[move_from] = true;
                grid[get_right_index(ag.current->i,ag.current->j, ROWS, COLS)].walls[3] = true;
                return (&grid[move_right(ag.current->i, ag.current->j, ROWS, COLS)]);
            } else{
                trapped = true;
            }
        } else if (move_from == 2) {
            if (!grid[get_down_index(ag.current->i, ag.current->j, ROWS, COLS)].visited) {
                push(ag.moved_cells, ag.current);
                push(ag.moves, "down");
                ag.current->walls[move_from] = true;
                grid[get_down_index(ag.current->i, ag.current->j, ROWS, COLS)].walls[0] = true;
                return (&grid[move_down(ag.current->i, ag.current->j, ROWS, COLS)]);
            } else{
                trapped = true;
            }
        } else if (move_from == 3) {
            if (!grid[get_left_index(ag.current->i, ag.current->j, ROWS, COLS)].visited) {
                push(ag.moved_cells, ag.current);
                push(ag.moves, "left");
                ag.current->walls[move_from] = true;
                grid[get_left_index(ag.current->i, ag.current->j, ROWS, COLS)].walls[1] = true;
                return (&grid[move_left(ag.current->i, ag.current->j, ROWS, COLS)]);
            } else{
                trapped = true;
            }
        }
    } else if (number_of_opened_walls == 2) {
        push(ag.moved_cells, ag.current);
        int picked = rand() % 4;
        while (ag.current->walls[picked])
            picked = rand() % 4;
        ag.current->walls[picked] = true;
        return ag.current;
    } else if(number_of_opened_walls==3){
        push(ag.moved_cells, ag.current);
        int picked = rand() % 4;
        while (ag.current->walls[picked])
            picked = rand() % 4;
        ag.current->walls[picked] = true;
        return ag.current;
    }
    else {
        int halfClosedindex = is_half_closed(ag.current, grid);
        if (halfClosedindex != -1) {
            ag.current->walls[halfClosedindex] = false;
        }
        if (is_full_closed(ag.current, grid)) {
            string temp = pop(ag.moves);
            if (temp == "top") {
                printf("moving down\n");
            } else if (temp == "right") {
                printf("moving left\n");
            } else if (temp == "down") {
                printf("moving top\n");
            } else if (temp == "left") {
                printf("moving right\n");
            }
        }
        int x = ag.current->j * CELL_WIDTH;
        int y = ag.current->i * CELL_WIDTH;
        GOval tempRect = newGOval(x + (CELL_WIDTH/4.0), y + (CELL_WIDTH/4.0), CELL_WIDTH - (CELL_WIDTH/2), CELL_WIDTH - (CELL_WIDTH/2));
        setFillColor(tempRect, "RED");
        setFilled(tempRect, true);
        add(panel, tempRect);
        return pop(ag.moved_cells);
    }

}

void draw_agent(agent ag, GWindow panel) {
    int x = ag.current->j * CELL_WIDTH;
    int y = ag.current->i * CELL_WIDTH;
    if (!ag.current->visited) {
        GOval tempRect = newGOval(x + (CELL_WIDTH/4.0), y + (CELL_WIDTH/4.0), CELL_WIDTH - (CELL_WIDTH/2), CELL_WIDTH - (CELL_WIDTH/2));
        setFillColor(tempRect, "GREEN");
        setFilled(tempRect, true);
        add(panel, tempRect);
    } else {
        GOval tempRect = newGOval(x + (CELL_WIDTH/4.0), y + (CELL_WIDTH/4.0), CELL_WIDTH - (CELL_WIDTH/2), CELL_WIDTH - (CELL_WIDTH/2));
        setFillColor(tempRect, "BLUE");
        setFilled(tempRect, true);
        add(panel, tempRect);
    }
    if (get_index(ag.current->i, ag.current->j, ROWS, COLS) == (END1)||get_index(ag.current->i, ag.current->j, ROWS, COLS) == (END2)) {
        GOval tempRect = newGOval(x + (CELL_WIDTH/4.0), y + (CELL_WIDTH/4.0), CELL_WIDTH - (CELL_WIDTH/2), CELL_WIDTH - (CELL_WIDTH/2));
        setFillColor(tempRect, "BLACK");
        setFilled(tempRect, true);
        add(panel, tempRect);
    }
    if (get_index(ag.current->i, ag.current->j, ROWS ,COLS)==START1 || get_index(ag.current->i, ag.current->j, ROWS ,COLS)==START2) {
        GOval tempRect = newGOval(x + (CELL_WIDTH/4.0), y + (CELL_WIDTH/4.0), CELL_WIDTH - (CELL_WIDTH/2), CELL_WIDTH - (CELL_WIDTH/2));
        setFillColor(tempRect, "WHITE");
        setFilled(tempRect, true);
        add(panel, tempRect);
    }


}
