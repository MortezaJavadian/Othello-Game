#include "GamePlay.h"

int NewGame()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    info GameInfo;
    info copy[2];

    strcpy(GameInfo.TypeStruct, "main");
    strcpy(copy[0].TypeStruct, "copy 1");
    strcpy(copy[1].TypeStruct, "copy 2");

    gotoxy(0, 1);
    printf("1.Classic Mode");
    gotoxy(4.5, 1);
    printf("2.Timer Mode");

    GameInfo.MODE = 0;
    gotoxy(0, 1);
    char movement;
    do
    {
        movement = getch();

        if (movement == Right && GameInfo.MODE < 4.5)
        {
            gotoxy(GameInfo.MODE += 4.5, 1);
        }
        else if (movement == Left && 0 < GameInfo.MODE)
        {
            gotoxy(GameInfo.MODE -= 4.5, 1);
        }
        else if (movement == Esc)
        {
            return 0;
        }

    } while (movement != '\r');

    if (GameInfo.MODE)
    {
        gotoxy(2.25, 2);
        printf("Game Time: ");
        scanf("%d", &GameInfo.minutes[0]);
        GameInfo.minutes[1] = GameInfo.minutes[0];

        if(GameInfo.minutes[0] < 10)
        {
            gotoxy(5.25, 2);
        }
        else
        {
            gotoxy(5.5, 2);
        }
        
        printf(" : ");
        scanf("%lf", &GameInfo.seconds[0]);
        GameInfo.seconds[1] = GameInfo.seconds[0];
        getchar();
    }

    clear();

    gotoxy(1, 1);
    printf("Name Player One: ");
    gotoxy(1, 2);
    printf("Name Player Two: ");

    gotoxy(5.25, 1);
    gets_s(GameInfo.NamePlayer[0], 40);

    gotoxy(5.25, 2);
    gets_s(GameInfo.NamePlayer[1], 40);

    //-------------------------------------------------------------------

    GameInfo.score[0] = 0;
    GameInfo.score[1] = 0;

    GameInfo.NumOfPieces[0] = 2;
    GameInfo.NumOfPieces[1] = 2;

    GameInfo.NumOfRequest[0] = 0;
    GameInfo.NumOfRequest[1] = 0;

    //-------------------------------------------------------------------

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            GameInfo.pieces[j][i] = ' ';
        }
    }

    //-------------------------------------------------------------------

    GameInfo.pieces[4][3] = 'B';
    GameInfo.pieces[3][4] = 'B';

    GameInfo.pieces[3][3] = 'W';
    GameInfo.pieces[4][4] = 'W';

    //-------------------------------------------------------------------

    GameInfo.pieces[3][2] = 'o';
    GameInfo.pieces[2][3] = 'o';
    GameInfo.pieces[5][4] = 'o';
    GameInfo.pieces[4][5] = 'o';

    //-------------------------------------------------------------------

    GameInfo.turn = 'B';

    //-------------------------------------------------------------------

    GameInfo.x = 3;
    GameInfo.y = 2;

    //-------------------------------------------------------------------

    if (GameInfo.MODE)
    {
        CopyTime(&GameInfo);
    }

    GameBackground(GameInfo, copy);

    return 0;
}