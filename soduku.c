#include <stdio.h>

#define N 9
#define UNASSIGNED '.'

int row[N][N], col[N][N], box[N][N];
char sudoku[N][N];

// Function to initialize row, col, and box arrays
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

// Function to solve the Sudoku puzzle
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
            row[i][k] = 1;
            col[j][k] = 1;
            box[(i/3)*3 + j/3][k] = 1;

            if (j == N-1) {
                if (solve(i+1, 0)) {
                    return 1;
                }
            } else {
                if (solve(i, j+1)) {
                    return 1;
                }
            }

            row[i][k] = 0;
            col[j][k] = 0;
            box[(i/3)*3 + j/3][k] = 0;
            sudoku[i][j] = UNASSIGNED;
        }
    }

    return 0;
}

// Function to print the solved Sudoku puzzle
void printSudoku() {
    int i, j;
    printf("\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%c", sudoku[i][j]);
        }
        
    }
}

int main() {
    int i, j;
    int count = 0;
    
    printf("Enter the Sudoku puzzle (use '.' for empty cells):\n");

    // Take input of the Sudoku puzzle
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf(" %c", &sudoku[i][j]);
            if (sudoku[i][j] != ' ') {
                count++;
            }
        }
    }

    // Check if the number of characters entered is 81
    if (count != 81) {
        printf("\nError: Enter exactly 81 characters.\n");
        return 1;
    }

    // Initialize the row, col, and box arrays
    initialize();
    printf("\n");
    // Solve the Sudoku puzzle
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%c", sudoku[i][j]);
        }
        
    }
    if (solve(0, 0)) {
        printf("\nSolution:\n");
        printSudoku();
    } else {
        printf("\nNo solution found.\n");
    }

    return 0;
}
