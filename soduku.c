/*Pallav Regmi*/
/*CS241-2DK*/
/*Lab04*/


#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 9
#define UNASSIGNED '.'
#define MAX_LINES 100  // maximum number of lines to read

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

void check_duplicate(char sudoku[N][N],int *x) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char current = sudoku[i][j];

            // Skip checking if the character is "."
            if (current == '.') {
                continue;
            }

            // Check for duplicates in the row
            for (int k = j+1 ; k < N; k++) {                
                if (sudoku[i][k] == current && sudoku[i][k] != '.') {
                    printf("\nError\n");
                    *x=1;
                    return;
                }
            }

            // Check for duplicates in the column
            for (int k = i + 1; k < N; k++) {
                if (sudoku[k][j] == current && sudoku[k][j] != '.') {
                    printf("\nError\n");
                    *x=1;
                    return;
                }
            }
        }
    }
}

void check_array(char arr[], int size, int* y) {
    for (int i = 0; i < size; i++) {
        char current = arr[i];
        if ((current < '0' || current > '9') && current != '.') {
            printf("\nError\n");
            *y=1;
            return;
        }
    }
}


int main() {
        int i, x , y;
        
        int capacity = 0; // current capacity of the array
    
        char ch;

        char *lines[MAX_LINES];  // array of pointers to hold each line
        char arr[100];  // buffer to hold each line
        int num_lines = 0;  // counter for the number of lines read
        FILE *file = fopen("testSudoku.in", "r");  // try to open the file for reading

        if (file == NULL) {
            //printf("File not found. Enter input from the terminal:\n");

            // read input lines from the terminal until EOF is reached
            while (fgets(arr, 100, stdin) != NULL && num_lines < MAX_LINES) {
                // allocate memory for the line and copy it into the array
                
                lines[num_lines] = malloc(sizeof(char) * (strlen(arr) + 1));
                strcpy(lines[num_lines], arr);
                num_lines++;
            }
        } else {
            // read input lines from the file until EOF is reached
            while (fgets(arr, 100, file) != NULL && num_lines < MAX_LINES) {
                // allocate memory for the line and copy it into the array
                
                lines[num_lines] = malloc(sizeof(char) * (strlen(arr) + 1));
                strcpy(lines[num_lines], arr);
                num_lines++;
                int size = 0;
                while (arr[size] != '\n') {
                    size++;
                }
                printf("\n");
                for (i = 0; i < size; i++) {
                    printf("%c", arr[i]);
                }

                //check if the arrary has anything other than numbers & "."s.
                y=0;
                check_array(arr, size, &y);
                if(y!=1){
                    // Check if the number of characters entered is 81
                    if (size != 81) {
                        printf("\nError\n");
                        
                    }else{
                    
                        // Take input of the Sudoku puzzle
                        int index = 0;
                        for (int i = 0; i < N; i++) {
                            for (int j = 0; j < N; j++) {
                                sudoku[i][j] = *(arr + index);
                                index++;
                            }
                        }
                        //checking for duplicates
                        x=0;
                        check_duplicate(sudoku,&x);
                        if(x!=1){
                            // Initialize the row, col, and box arrays
                            initialize();
                            // Solve the Sudoku puzzle
                            if (solve(0, 0)) {
                                printSudoku();
                                printf("\n");
                            } else {
                                printf("\nNo solution\n");
                            }
                        }
                    }
                }
                
            }

            fclose(file);  // close the file when we're done
        }
        for (int i = 0; i < num_lines; i++) {
            //printf("%s",lines[i]);
            free(lines[i]);  
        }
    return 0;

}
