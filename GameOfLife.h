#pragma once
#include "GameBoard.h"

int count_nbr(int **board_, int i, int j, int height, int width)
{
    int nbr_count = 0;
    /* Stores the count of vertical,horizontal,diagonal alive neighbours */
    if (i - 1 >= 0 && j - 1 >= 0)
    {
        if (board_[i - 1][j - 1] >= 1)
            nbr_count++;
    }

    if (i - 1 >= 0)
    {
        if (board_[i - 1][j] >= 1)
            nbr_count++;
    }

    if (i - 1 >= 0 && j + 1 < width)
    {
        if (board_[i - 1][j + 1] >= 1)
            nbr_count++;
    }

    if (j - 1 >= 0)
    {
        if (board_[i][j - 1] >= 1)
            nbr_count++;
    }

    if (j + 1 < width)
    {
        if (board_[i][j + 1] >= 1)
            nbr_count++;
    }

    if (i + 1 < height && j - 1 >= 0)
    {
        if (board_[i + 1][j - 1] >= 1)
            nbr_count++;
    }

    if (i + 1 < height)
    {
        if (board_[i + 1][j] >= 1)
            nbr_count++;
    }

    if (i + 1 < height && j + 1 < width)
    {
        if (board_[i + 1][j + 1] >= 1)
            nbr_count++;
    }

    return nbr_count;
}
void playTheGame(char *argv[])
{
    int bheight = 0;              /* Game board Height*/
    int bwidth = 0;               /* Game board Width*/
    int **board = NULL;           /* Game Board data*/
    int **neighbour_count = NULL; /* 2D array to store every cell's neighbours count information*/
    int row1 = 0;                 /* will be used for file reading*/
    int col1 = 0;                 /* will be used for file reading*/
    int fileOpenFlag = 0;
    int i, j, steps;
    int MAX_Steps = 0;
    int fileWithErrorFlag;
    FILE *file;
    fileWithErrorFlag = 0;
    file = fopen(argv[1], "r"); /* Opening file given in comandline arguments*/
    if (file == NULL)
    {
        fileOpenFlag = 1;
        fileWithErrorFlag = 1;
        printf("file can't be opened \n");
    }
    if (fileOpenFlag == 0)
    {
        char str[100];
        int flag = 1; /* To help read only the first line*/
        while (fgets(str, 100, file) != NULL)
        {
            if (flag == 1)
            {
                int index;
                /* Reading game boundary*/
                char Height[5];
                char Width[5];
                i = 0;
                index = 0;
                for (; str[i] != ' '; i++)
                {
                    Height[index] = str[i];
                    index++;
                }
                Height[index] = '\0';
                index = 0;
                for (; str[i] != '\0'; i++)
                {
                    Width[index] = str[i];
                    index++;
                }
                Width[index] = '\0';
                bwidth = atoi(Width);                                  /* Setting the Width of Table to Draw*/
                bheight = atoi(Height);                                /* Setting the Height of Table to Draw*/
                board = create_empty_board(bheight, bwidth);           /* Creating GameBord*/
                neighbour_count = create_empty_board(bheight, bwidth); /* initilazing*/
                flag = 0;                                              /* First line reading Done*/
                i = 0;
            }
            else
            {
                col1 = 0; /* reset col1 value for every new row*/
                /* Reading Board Data from File and Storng it in Game Board*/
                for (i = 0; str[i] != '\0'; i++)
                {
                    if (row1 < bheight && col1 < bwidth)
                    {
                        /* storing data in board*/
                        if (str[i] == '1')
                        {
                            board[row1][col1] = 1;
                            col1++;
                        }
                        else if (str[i] == '0')
                        {
                            board[row1][col1] = 0;
                            col1++;
                        }
                        else if (str[i] != ' ')
                        {
                            fileWithErrorFlag = 1;
                            printf("Wrong data in File\n");
                            break;
                        }
                    }
                    else
                    {
                        fileWithErrorFlag = 1;
                        printf("Wrong data in File\n");
                        break;
                    }
                }
                row1++; /* go to next row in board*/
                i = 0;
            }
        }
        /* End of File reading*/
        fclose(file); /* Closing file*/
        if (fileWithErrorFlag == 0)
        {
            MAX_Steps = atoi(argv[2]); /* from camand line arguments reading max itrations*/
            if (MAX_Steps > 0)
            {
                for (steps = 0; steps < MAX_Steps; ++steps)
                {
                    system("clear"); /* Clearing terminal*/
                    printf("\n");
                    for (i = 0; i < bheight; i++)
                    {
                        for (j = 0; j < bwidth; j++)
                        {
                            if (board[i][j] == 1) /* printing black box*/
                            {
                                printf("\033[0;100m");
                                printf("  ");
                            }
                            else /* printing white box*/
                            {
                                printf("\033[0;107m");
                                printf("  ");
                            }
                            printf("\033[0m"); /* resetting background colour*/
                            /* updating neighbours of every cell*/
                            neighbour_count[i][j] = count_nbr(board, i, j, bheight, bwidth);
                        }
                        printf("\n");
                    }

                    for (i = 0; i < bheight; ++i)
                    {
                        for (j = 0; j < bwidth; ++j)
                        {
                            if (board[i][j] >= 1)
                            {
                                if (neighbour_count[i][j] <= 1 || neighbour_count[i][j] >= 4) /* Checking Conditions of cell's death in next genration  (Low population & Over population)*/
                                    board[i][j] = 0;
                            }
                            else if (neighbour_count[i][j] == 3) /* Checking Condition of cell's life in next genration (Exactly 3 neighbours)*/
                                board[i][j] = 1;
                        }
                    }

                    printf("\n");
                    system("sleep 1");
                }
            }
            else
            {
                printf("Number of Cycles must be a Positive Number\n");
            }
            /* Deleting the dynamic memory*/
            for (i = 0; i < bheight; i++)
            {
                free(board[i]);
                free(neighbour_count[i]);
            }
            free(board);
            free(neighbour_count);
        }
    }
}
