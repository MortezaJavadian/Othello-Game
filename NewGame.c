#include "GamePlay.h"
#include "json.h"
#include "secret.h"

int NewGame()
{
    PrintBorder();
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    info GameInfo;
    info copy[2];

    strcpy(GameInfo.TypeStruct, "main");
    strcpy(copy[0].TypeStruct, "copy 1");
    strcpy(copy[1].TypeStruct, "copy 2");

    gotoxy(2, 2);
    printf("1.Classic Mode");
    gotoxy(6.5, 2);
    printf("2.Timer Mode");

    GameInfo.MODE = 2;
    gotoxy(2, 2);
    char movement;
    do
    {
        movement = getch();

        if (movement == Right && GameInfo.MODE < 6.5)
        {
            gotoxy(GameInfo.MODE += 4.5, 2);
        }
        else if (movement == Left && 2 < GameInfo.MODE)
        {
            gotoxy(GameInfo.MODE -= 4.5, 2);
        }
        else if (movement == Esc)
        {
            return 0;
        }

    } while (movement != '\r');

    GameInfo.MODE -= 2;

    if (GameInfo.MODE)
    {
        gotoxy(4.25, 3);
        printf("Game Time: ");
        scanf("%d", &GameInfo.minutes[0]);
        GameInfo.minutes[1] = GameInfo.minutes[0];

        if (GameInfo.minutes[0] < 10)
        {
            gotoxy(7.25, 3);
        }
        else
        {
            gotoxy(7.5, 3);
        }

        printf(" : ");
        scanf("%lf", &GameInfo.seconds[0]);
        GameInfo.seconds[1] = GameInfo.seconds[0];
        getchar();
    }
    //-------------------------------------------------------------------

    PrintBorder();

    //-------------------------------------------------------------------

    GameInfo.NamePlayer[0][0] = 0;
    GameInfo.NamePlayer[1][0] = 0;

    gotoxy(3, 2);
    printf("Name Player One: ");
    gotoxy(3, 3);
    printf("Name Player Two: ");

    do
    {
        gotoxy(7.25, 2);
        gets_s(GameInfo.NamePlayer[0], 40);

        if (GameInfo.NamePlayer[0][0] == 0)
        {
            gotoxy(3, 1);
            printf("Your nmae can't be blank!!               ");
        }

    } while (GameInfo.NamePlayer[0][0] == 0);
    gotoxy(3, 1);
    printf("                                         ");

    do
    {
        gotoxy(7.25, 3);
        gets_s(GameInfo.NamePlayer[1], 40);

        if (GameInfo.NamePlayer[1][0] == 0)
        {
            gotoxy(3, 1);
            printf("Your nmae can't be blank!!               ");
        }
        else if(!strcmp(GameInfo.NamePlayer[0],GameInfo.NamePlayer[1]))
        {
            gotoxy(7.25, 3);
            printf("                                       ");
            gotoxy(3, 1);
            printf("Your nmae can't be same with player one!!");
        }

    } while (GameInfo.NamePlayer[1][0] == 0 || !strcmp(GameInfo.NamePlayer[0],GameInfo.NamePlayer[1]));
    gotoxy(3, 1);
    printf("                                         ");

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

    //-------------------------------------------------------------------

    int mode = GameBackground(&GameInfo, copy);

    if (mode == End)
    {
        char name[] = "Score.json";
        ToJson(GameInfo, name);

        FILE *SaveFile = fopen(name, "r");
        ToSecret(SaveFile, name);
        fclose(SaveFile);
    }
    else if (mode == Unfinished)
    {
        char NameFile[] = "Unfinished.json";

        ToJson(GameInfo, NameFile);
        if (GameInfo.MODE)
        {
            ToJson(copy[0], NameFile);
            ToJson(copy[1], NameFile);
        }

        FILE *SaveFile = fopen("Unfinished.json", "r");
        ToSecret(SaveFile, NameFile);
        fclose(SaveFile);
    }

    return 0;
}