#include <stdio.h>

#include "HomePage"
#include "NewGame"

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
            printf("salam");
            break;

        case 3:
            break;

        case 4:
            return 0;
        }

    } while (1);
}