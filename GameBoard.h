#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int **create_empty_board(int height, int width) /* creating and intialization of game board*/
{
    int **board = (int **)malloc(height * sizeof(int *));
    int i = 0;
    for (i = 0; i < height; i++)
        board[i] = (int *)malloc(width * sizeof(int));
    for (i = 0; i < height; i++)
    {
        int j = 0;
        for (j = 0; j < width; j++)
        {
            board[i][j] = 0;
        }
    }
    return board;
}
void printBoard(int **board_, int bheight, int bwidth)
{
    int i,j;
    for (i = 0; i < bheight; i++)
    {
        for (j = 0; j < bwidth; j++)
        {
            if (board_[i][j] == 1)
            {
                printf("\033[0;100m");
                printf("  ");
            }
            else
            {
                printf("\033[0;107m");
                printf("  ");
            }
            printf("\033[0m");
        }
        printf("\n");
    }
}