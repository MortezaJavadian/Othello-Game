#include "GamePlay.h"

int main()
{
    char NameFile[] = "Unfinished.json";
    FILE *file = fopen("Unfinished.json", "r");

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
            break;

        case 4:
            return 0;
        }

    } while (1);
}