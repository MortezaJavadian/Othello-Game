#include "GamePlay.h"
#include "json.h"

int NewGame()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    info GameInfo;
    info copy[2];

    GameInfo.TypeStruct = 1;
    copy[0].TypeStruct = 2;
    copy[1].TypeStruct = 3;

    gotoxy(0, 1);
    printf("1.Classic Mode");
    gotoxy(4.5, 1);
    printf("2.Timer Mode");

    GameInfo.MODE = 0;
    gotoxy(0, 1);
    char movement1;
    do
    {
        movement1 = getch();

        if (movement1 == Right && GameInfo.MODE < 4.5)
        {
            gotoxy(GameInfo.MODE += 4.5, 1);
        }
        else if (movement1 == Left && 0 < GameInfo.MODE)
        {
            gotoxy(GameInfo.MODE -= 4.5, 1);
        }

    } while (movement1 != '\r');

    if (GameInfo.MODE)
    {
        gotoxy(2.25, 2);
        printf("Game Time: ");
        scanf("%d", &GameInfo.minutes[0]);
        GameInfo.minutes[1] = GameInfo.minutes[0];

        gotoxy(5.5, 2);
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

    PrintBoard();

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

    PrintInfo(&GameInfo);

    //-------------------------------------------------------------------

    if (GameInfo.MODE)
    {
        CopyTime(&GameInfo);
    }

    //-------------------------------------------------------------------

    char movement = '\0';
    do
    {
        if (GameInfo.MODE && movement != '\0')
        {
            timer(&GameInfo);

            if (GameInfo.minutes[0] <= 0 && GameInfo.seconds[0] <= 0)
            {
                gotoxy(11, 4);
                printf("Winer is W ' %s '", GameInfo.NamePlayer[1]);
                gotoxy(0, 8);
                return 0;
            }
            else if (GameInfo.minutes[1] <= 0 && GameInfo.seconds[1] <= 0)
            {
                gotoxy(11, 4);
                printf("Winer is B ' %s '", GameInfo.NamePlayer[0]);
                gotoxy(0, 8);
                return 0;
            }
        }

        movement = getch();
        if (movement == Down && GameInfo.y < 7)
        {
            gotoxy(GameInfo.x, ++GameInfo.y);
        }
        else if (movement == Up && 0 < GameInfo.y)
        {
            gotoxy(GameInfo.x, --GameInfo.y);
        }
        else if (movement == Right && GameInfo.x < 7)
        {
            gotoxy(++GameInfo.x, GameInfo.y);
        }
        else if (movement == Left && 0 < GameInfo.x)
        {
            gotoxy(--GameInfo.x, GameInfo.y);
        }
        else if (movement == '\r' && GameInfo.pieces[GameInfo.x][GameInfo.y] != 'o')
        {
            gotoxy(11, 4);
            printf("You can't");
            gotoxy(GameInfo.x, GameInfo.y);
            Sleep(750);
            gotoxy(11, 4);
            printf("         ");
            gotoxy(GameInfo.x, GameInfo.y);
        }

        //-------------------------------------------------------------------

        else if (GameInfo.MODE && (movement == Backspace) && (GameInfo.NumOfRequest[0] != 2 || GameInfo.NumOfRequest[1] != 2))
        {
            gotoxy(11, 5);
            printf("Who has requested the game back?");
            gotoxy(11, 6);
            printf("1.B   2.W");
            gotoxy(11, 6);

            char movement2;
            double x2 = 11;
            do
            {
                movement2 = getch();

                if (movement2 == Right && x2 < 12.5)
                {
                    gotoxy(x2 += 1.5, 6);
                }
                else if (movement2 == Left && 11 < x2)
                {
                    gotoxy(x2 -= 1.5, 6);
                }

            } while (movement2 != '\r' || GameInfo.NumOfRequest[(x2 == 11) ? 0 : 1] == 2);

            gotoxy(11, 5);
            printf("                                ");
            gotoxy(11, 6);
            printf("         ");

            GameInfo.RequestBack = (x2 == 11) ? 0 : 1;

            GameInfo.NumOfRequest[GameInfo.RequestBack]++;

            PasteInfo(&GameInfo, copy);
            CopyTime(&GameInfo);
            PrintInfo(&GameInfo);
        }

        //-------------------------------------------------------------------

        else if (movement == '\r' && GameInfo.pieces[GameInfo.x][GameInfo.y] == 'o')
        {
            if (GameInfo.turn == 'B')
            {
                if (GameInfo.MODE)
                {
                    CopyInfo(&GameInfo, copy);
                }

                GameInfo.pieces[GameInfo.x][GameInfo.y] = 'B';
                GameInfo.turn = 'W';
            }
            else if (GameInfo.turn == 'W')
            {
                if (GameInfo.MODE)
                {
                    CopyInfo(&GameInfo, copy);
                }

                GameInfo.pieces[GameInfo.x][GameInfo.y] = 'W';
                GameInfo.turn = 'B';
            }

            int ScoreMove = RotatePieces_Score(GameInfo.pieces, GameInfo.x, GameInfo.y);
            GameInfo.score[(GameInfo.turn == 'B') ? 1 : 0] += ScoreMove;

            GameInfo.NumOfPieces[(GameInfo.turn == 'B') ? 1 : 0] += ScoreMove + 1;
            GameInfo.NumOfPieces[(GameInfo.turn == 'B') ? 0 : 1] -= ScoreMove;

            LegalMoves(GameInfo.pieces, GameInfo.turn);

            if (GameInfo.MODE)
            {
                CopyTime(&GameInfo);
            }

            if (CheckTurn(GameInfo.pieces, GameInfo.turn))
            {
                PrintInfo(&GameInfo);
            }
            else
            {
                GameInfo.turn = (GameInfo.turn == 'B') ? 'W' : 'B';

                LegalMoves(GameInfo.pieces, GameInfo.turn);

                PrintInfo(&GameInfo);

                if (!CheckTurn(GameInfo.pieces, GameInfo.turn))
                {
                    char winer = (GameInfo.NumOfPieces[0] > GameInfo.NumOfPieces[1]) ? 'B' : 'W';

                    char NameWiner[40];
                    strcpy(NameWiner, (winer == 'B') ? GameInfo.NamePlayer[0] : GameInfo.NamePlayer[1]);

                    gotoxy(11, 4);
                    printf("Winer is %c ' %s '", winer, NameWiner);
                    gotoxy(0, 8);
                    return 0;
                }
            }
        }

        //-------------------------------------------------------------------

        else if (movement == Esc)
        {
            FILE *SaveFile;

            SaveFile = fopen("save.json", "a+");

            ToJson(SaveFile, GameInfo);

            return 0;
        }

    } while (1);
}