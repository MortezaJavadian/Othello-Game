#include "GamePlay.h"

int main()
{
    do
    {
        switch (HomePage())
        {
        case 1:
            NewGame();
            break;

        case 2:
            UnfinishedGame();
            break;

        case 3:
            Score();
            break;

        case 4:
            return 0;
        }

    } while (1);
}