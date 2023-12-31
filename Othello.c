#include <stdio.h>

#include "HomePage"
#include "NewGame"

int main()
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
        return 0;
    }

    return 0;
}