#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int **create_empty_board(int height, int width) // creating and intialization of game board
{
    int **board = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++)
        board[i] = (int *)malloc(width * sizeof(int));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            board[i][j] = 0;
        }
    }
    return board;
}
void printBoard(int** board_,int bheight,int bwidth)
{
    for(int i=0;i<bheight;i++)
    {
        for(int j=0;j<bwidth;j++)
        {
            if (board_[i][j] == 1)
            {
                printf("\033[0;100m");
                printf("  ");
            }else
            {
                printf("\033[0;107m");
                printf("  ");
            }
            printf("\033[0m");
        }
        printf("\n");
    }
}
int count_nbr(int **board_, int i, int j, int height, int width)
{
    int nbr_count = 0; // Stores the count of vertical,horizontal,diagonal alive neighbours
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
int main(int argc,char*argv[])
{
    int bheight = 0;    // Game board Height
    int bwidth = 0;     // Game board Width
    int **board = NULL; // Game Board data
    int **neighbour_count=NULL; // 2D array to store every cell's neighbours count information
    int row1=0; //will be used for file reading
    int col1=0; //will be used for file reading

    FILE *file;
    file = fopen(argv[1], "r"); // Opening file given in comandline arguments
    if (file == NULL)
    {
        printf("file can't be opened \n");
        return -1;
    }
    char str[100];
    int flag = 1; // To help read only the first line
    while (fgets(str, 100, file) != NULL)
    {
        if (flag == 1)
        {
            // Reading game boundary
            char Height[5];
            char Width[5];
            int i = 0;
            int index = 0;
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
            bwidth = atoi(Width);   // Setting the Width of Table to Draw
            bheight = atoi(Height); // Setting the Height of Table to Draw
            board = create_empty_board(bheight,bwidth); //Creating GameBord
            neighbour_count=create_empty_board(bheight,bwidth);//initilazing
            flag = 0;   //First line reading Done
        }
        else
        {
            col1=0; //reset col1 value for every new row
            // Reading Board Data from File and Storng it in Game Board
            for(int i=0;str[i]!='\0';i++)
            {
                //storing data in board
                if(str[i]=='1')
                {
                    board[row1][col1]=1;
                    col1++;
                }else if(str[i]=='0')
                {
                    board[row1][col1] = 0;
                    col1++;
                }
            }
            row1++; //go to next row in board
        }
    }
    // End of File reading
    fclose(file); // Closing file

    int i, j, steps;
    int MAX_Steps = atoi(argv[2]);  //from camand line arguments reading max itrations
    for (steps = 0; steps < MAX_Steps; ++steps)
    {
        system("clear");    //Clearing terminal
        printf("\n");
        for (int i = 0; i < bheight; i++)
        {
            for (int j = 0; j < bwidth; j++)
            {
                if (board[i][j] == 1)   //printing black box
                {
                    printf("\033[0;100m");
                    printf("  ");
                }
                else                   //printing white box
                {
                    printf("\033[0;107m");  
                    printf("  ");
                }
                printf("\033[0m");     //resetting background colour
                // updating neighbours of every cell 
                neighbour_count[i][j] = count_nbr(board, i, j, bheight,bwidth);
            }
            printf("\n");
        }

        for (i = 0; i < bheight; ++i)
        {
            for (j = 0; j < bwidth; ++j)
            {
                if (board[i][j] >= 1)
                {
                    if (neighbour_count[i][j] <= 1 || neighbour_count[i][j] >= 4) // Checking Conditions of cell's death in next genration
                        board[i][j] = 0;
                }
                else if (neighbour_count[i][j] == 3) // Checking Condition of cell's life in next genration
                    board[i][j] = 1;
            }
        }

        printf("\n");
        system("sleep 1");
    }
    for (int i = 0; i < bheight; i++)
    {
        free(board[i]);
        free(neighbour_count[i]);
    }
    free(board);
    free(neighbour_count);
    return 0;
    }
