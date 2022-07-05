#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#define DEAD 95
#define ALIVE 64
#define HEIGHT 25
#define LENGTH 80

void print(char board[][LENGTH], WINDOW * wnd);
void change_state(char board_read[][LENGTH], char board_result[][LENGTH]);
void copy(char board_read[][LENGTH], char board_result[][LENGTH]);
void count(char board_read[][LENGTH], int *count_alive, int y, int x);
void positions(int *up, int *down, int *left, int *right, int y, int x);
void generate_field(char board[][LENGTH], char board_changed[][LENGTH]);
void nullify(char board_read[][LENGTH], char board_changed[][LENGTH]);

int main() {
    char board[HEIGHT][LENGTH], board_changed[HEIGHT][LENGTH];
    WINDOW * wnd;
    int speed = 500000;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    wnd = newwin(HEIGHT + 4, LENGTH + 3, 0, 0);
    if (has_colors() == 1) {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        wattrset(wnd, COLOR_PAIR(1));
    }
    nodelay(wnd, 1);
    nullify(board, board_changed);
    generate_field(board, board_changed);
    print(board, wnd);
    while (1) {
        change_state(board, board_changed);
        print(board_changed, wnd);
        copy(board_changed, board);
        usleep(speed);
        change_state(board_changed, board);
        print(board, wnd);
        copy(board, board_changed);
        char key = wgetch(wnd);
        if (key == 'q') {
            break;
        }
        if (key == '1') {
            speed = 500000;
            flushinp();
        }
        if (key == '2') {
            speed = 250000;
            flushinp();
        }
        if (key == '3') {
            speed = 150000;
            flushinp();
        }
        if (key == '4') {
            speed = 50000;
            flushinp();
        }
        if (key == '5') {
            speed = 10000;
            flushinp();
        }
        usleep(speed);
    }
    endwin();
    return 0;
}

void print(char board[][LENGTH], WINDOW * wnd) {
    wmove(wnd, 0, 0);
    wprintw(wnd, "\t\t\tPRESS 1-5 TO SWITCH SPEED, Q TO QUIT\n");
    for (int i = 0; i < LENGTH + 2; i++)
            wprintw(wnd, "_");
        wprintw(wnd, "\n");
    for (int i = 0; i < HEIGHT; i++) {
        wprintw(wnd, "|");
        for (int j = 0; j < LENGTH; j++) {
            if (board[i][j] == ALIVE) {
                wprintw(wnd, "@");
            } else {
                wprintw(wnd, " ");
            }
        }
        wprintw(wnd, "|\n");
    }
    for (int m = 0; m < LENGTH + 2; m++)
        wprintw(wnd, "-");
    wprintw(wnd, "\n");
    wrefresh(wnd);
}
void change_state(char board_read[][LENGTH], char board_result[][LENGTH]) {
    int count_alive;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < LENGTH; j++) {
            count_alive = 0;
            count(board_read, &count_alive, i, j);
            if (board_read[i][j] == DEAD) {
                if (count_alive == 3) {
                    board_result[i][j] = ALIVE;
                }
            }
            if (board_read[i][j] == ALIVE) {
                if (count_alive > 3) {
                    board_result[i][j] = DEAD;
                }
                if (count_alive < 2) {
                    board_result[i][j] = DEAD;
                }
            }
        }
    }
}
void copy(char board_read[][LENGTH], char board_result[][LENGTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < LENGTH; j++) {
                board_result[i][j] = board_read[i][j];
        }
    }
}
void count(char board_read[][LENGTH], int *count_alive, int y, int x) {
    int down, up, left, right;
    positions(&up, &down, &left, &right, y, x);
                if (board_read[up][x] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
                if (board_read[up][right] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
                if (board_read[up][left] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
                if (board_read[y][right] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
                if (board_read[y][left] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
                if (board_read[down][x] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
                if (board_read[down][right] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
                if (board_read[down][left] == ALIVE) {
                    *count_alive = *count_alive + 1;
                }
}
void positions(int *up, int *down, int *left, int *right, int y, int x) {
    *down = y + 1;
        if (y == HEIGHT - 1) {
            *down = 0;
        }
    *up = y - 1;
        if (y == 0) {
            *up = HEIGHT - 1;
        }
    *left = x - 1;
        if (x == 0) {
            *left = LENGTH - 1;
        }
    *right = x + 1;
        if (x == LENGTH - 1) {
            *right = 0;
        }
}
void generate_field(char board_read[][LENGTH], char board_changed[][LENGTH]) {
    char c;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < LENGTH; j++) {
            c = getchar();
            if (c == '1') {
                board_read[i][j] = ALIVE;
                board_changed[i][j] = ALIVE;
            }
            if (c == '\n') {
                break;
            }
        }
    }
    if (freopen("/dev/tty", "r", stdin)) {;}
}
void nullify(char board_read[][LENGTH], char board_changed[][LENGTH]) {
  for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < LENGTH; j++) {
            board_read[i][j] = DEAD;
            board_changed[i][j] = DEAD;
        }
    }
}

