#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

int counter = 0; ///Used for checking the validity of a solution

int EmptyPlace(int sudoku[9][9], short* row, short* column)
{
    for (*row = 0; *row < 9; (*row)++)
        for (*column = 0; *column < 9; (*column)++)
            if (sudoku[*row][*column] == 0)
                return 1;
    return 0;
}

int RowValid(int sudoku[9][9], short row, short number)
{
    for (short column = 0; column < 9; column++)
        if (sudoku[row][column] == number)
            return 1;
    return 0;
}

int ColumnValid(int sudoku[9][9], short column, short number)
{
    for (short row = 0; row < 9; row++)
        if (sudoku[row][column] == number)
            return 1;
    return 0;
}

int BoxValid(int sudoku[9][9], int rowStart, int columnStart, int number)
{
    for (int row = 0; row < 3; row++)
        for (int column = 0; column < 3; column++)
            if (sudoku[row + rowStart][column + columnStart] == number)
                return 1;
    return 0;
}

int ValidInsertion(int sudoku[9][9], short row, short column, short number)
{
    return (RowValid(sudoku, row, number) == 0 &&
        ColumnValid(sudoku, column, number) == 0 &&
        BoxValid(sudoku, row - row % 3, column - column % 3, number) == 0 &&
        sudoku[row][column] == 0);
}

int SolveSudoku(int sudoku[9][9])
{
    short row, column;
    if (EmptyPlace(sudoku, &row, &column) == 0)
        return 1;

    for (short number = 1; number <= 9; number++)
    {
        if (ValidInsertion(sudoku, row, column, number) == 1)
        {
            sudoku[row][column] = number;

            if (SolveSudoku(sudoku) != 0)
                return 1;

            sudoku[row][column] = 0;
        }
    }

    return 0;
}

void SolveAllSudoku(int sudoku[9][9])
{
    short row, column;
    if (EmptyPlace(sudoku, &row, &column) == 0)
        counter++;

    for (short number = 1; number <= 9; number++)
    {
        if (ValidInsertion(sudoku, row, column, number) == 1)
        {
            sudoku[row][column] = number;
            SolveAllSudoku(sudoku);
            sudoku[row][column] = 0;
        }
    }

    //return 0;
}


void PrintSolution(int sudoku[9][9])
{
    printf("%c", 201);
    for (int i = 0; i < 23; i++)
        if (i != 7 && i != 15)
            printf("%c", 205);
        else
            printf("%c", 203);
    printf("%c\n", 187); // Drawing the upper line of the sudoku

    for (short i = 0; i < 9; ++i)
    {
        if (i % 3 == 0 && i != 0)
        {
            printf("%c", 204);
            for (int i = 0; i < 23; i++)
                if (i != 7 && i != 15)
                    printf("%c", 205);
                else
                    printf("%c", 206);
            printf("%c\n", 185); // The midlines
        }

        printf("%c ", 186);
        for (short j = 0; j < 9; ++j)
        {
            if (j % 3 == 0 && j != 0)
                printf("%c ", 186);
            printf("%d ", sudoku[i][j]);
            if (j == 8)
                printf("%c", 186);
        }

        printf("\n");
    }

    printf("%c", 200);
    for (int i = 0; i < 23; i++)
        if (i == 7 || i == 15)
            printf("%c", 202);
        else
            printf("%c", 205);
    printf("%c\n", 188);
}

void UnsolveSudoku(int sudoku[9][9], int number)
{
    for (int i = 0; i < number; ++i)
    {
        int row = rand() % 9;
        int column = rand() % 9;
        int aux = sudoku[row][column];
        if (aux != 0)
        {
            sudoku[row][column] = 0;
            SolveAllSudoku(sudoku);
            if (counter != 1)
            {
                sudoku[row][column] = aux;
                i--;
            }
            counter = 0;
        }
        else
            i--;
    }
}

int main()
{
	int sudoku[9][9];
	srand((unsigned)time(0));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			sudoku[i][j] = 0;
	sudoku[rand() % 9][rand() % 9] = rand() % 9 + 1;
	
	printf("Here's our sudoku base: \n");
	PrintSolution(sudoku);

	printf("Here is a possible sudoku board fully completed: \n");
	if (SolveSudoku(sudoku) == true)
		PrintSolution(sudoku);
	else
		printf("There is no valid solution\n");

	UnsolveSudoku(sudoku,50);
	printf("Here is a sudoku board after removing some of the values: \n");
	PrintSolution(sudoku);

	SolveAllSudoku(sudoku);
	printf("The number of solutions for this puzzle is always: %d\n", counter);
	return 0;
}

