#include"GameOfLife.h"
int main(int argc,char* argv[])
{
    if(argc==3)
    {
        playTheGame(argv);
    }else if(argc>3)
    {
        printf("Too Many Arguments\n");
    }
    else
    {
        printf("Too Few Arguments\n");
    }
    return 0;
}