pregmi@setebos:~/cs241/lab04$ gcc -Wall -ansi -pedantic sudoku.c
/*Pallav Regmi*/
/*CS241-2DK*/
/*Lab04*/


#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define N 9
#define UNASSIGNED '.'
#define CHUNK_SIZE 10

int row[N][N], col[N][N], box[N][N];
char sudoku[N][N];

/*Function to initialize row, col, and box arrays*/
void initialize() {
    int i, j, k;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            row[i][j] = 0;
            col[i][j] = 0;
            box[i][j] = 0;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (sudoku[i][j] != UNASSIGNED) {
                k = sudoku[i][j] - '1';

                row[i][k] = 1;
                col[j][k] = 1;
                box[(i/3)*3 + j/3][k] = 1;
            }
        }
    }
}

/*Function to solve the Sudoku puzzle*/
int solve(int i, int j) {
    int k;

    if (i == N) {
        return 1;
    }

    if (sudoku[i][j] != UNASSIGNED) {
        if (j == N-1) {
            return solve(i+1, 0);
        } else {
            return solve(i, j+1);
        }
    }

    for (k = 0; k < N; k++) {
        if (!row[i][k] && !col[j][k] && !box[(i/3)*3 + j/3][k]) {
            sudoku[i][j] = k + '1';
-UU-:----F1  sudoku.c       Top L1     (C/*l Abbrev) -------------------------------------------------------------------------------------------------------------------------------------------------------
For information about GNU Emacs and the GNU system, type C-h C-a.
