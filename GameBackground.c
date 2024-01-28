#include "GamePlay.h"

int GameBackground(info *GameInfo, info copy[2])
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    //-------------------------------------------------------------------

    if (GameInfo->MODE)
    {
        gotoxy(9, 5);
        printf("Everyone wants to go back,");
        gotoxy(9, 5.5);
        printf("press the Backspace key.");
    }

    int FlatB_back = 0;
    int FlatW_back = 0;
    int FlatBack = 1;


    //-------------------------------------------------------------------

    PrintBorder();

    PrintBoard();

    PrintInfo(GameInfo);

    //-------------------------------------------------------------------

    char movement = '\0';
    do
    {
        if (GameInfo->MODE && movement != '\0')
        {
            timer(GameInfo);

            if (GameInfo->minutes[0] <= 0 && GameInfo->seconds[0] <= 0)
            {
                GameInfo->score[0] = 0;
                gotoxy(11, 4);
                printf("Winer is W ' %s '", GameInfo->NamePlayer[1]);
                gotoxy(0, 8);

                char movement1;
                do
                {
                    movement1 = getch();

                } while (movement1 != Esc);

                return End;
            }
            else if (GameInfo->minutes[1] <= 0 && GameInfo->seconds[1] <= 0)
            {
                GameInfo->score[1] = 0;
                gotoxy(11, 4);
                printf("Winer is B ' %s '", GameInfo->NamePlayer[0]);
                gotoxy(0, 8);

                char movement1;
                do
                {
                    movement1 = getch();

                } while (movement1 != Esc);

                return End;
            }
        }

        movement = getch();
        if (movement == Down && GameInfo->y < 7)
        {
            gotoxy(GameInfo->x, ++GameInfo->y);
        }
        else if (movement == Up && 0 < GameInfo->y)
        {
            gotoxy(GameInfo->x, --GameInfo->y);
        }
        else if (movement == Right && GameInfo->x < 7)
        {
            gotoxy(++GameInfo->x, GameInfo->y);
        }
        else if (movement == Left && 0 < GameInfo->x)
        {
            gotoxy(--GameInfo->x, GameInfo->y);
        }
        else if (movement == '\r' && GameInfo->pieces[GameInfo->x][GameInfo->y] != 'o')
        {
            gotoxy(11, 4);
            printf("You can't");
            gotoxy(GameInfo->x, GameInfo->y);
            Sleep(750);
            gotoxy(11, 4);
            printf("         ");
            gotoxy(GameInfo->x, GameInfo->y);
        }

        //-------------------------------------------------------------------

        else if (GameInfo->MODE && (movement == Backspace) && (GameInfo->NumOfRequest[0] != 2 || GameInfo->NumOfRequest[1] != 2) && (FlatB_back || FlatW_back) && FlatBack)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            gotoxy(8.5, 5);
            printf("Who has requested the game back?");
            gotoxy(9, 5.5);
            printf("                        ");
            gotoxy(10, 6);
            printf("1.B   2.W");
            gotoxy(10, 6);

            char movement2;
            double x2 = 10;
            do
            {
                movement2 = getch();

                if (movement2 == Right && x2 < 11.5)
                {
                    gotoxy(x2 += 1.5, 6);
                }
                else if (movement2 == Left && 10 < x2)
                {
                    gotoxy(x2 -= 1.5, 6);
                }

            } while (movement2 != '\r' || GameInfo->NumOfRequest[(x2 == 10) ? 0 : 1] == 2 || ((x2 == 10) ? !FlatB_back : !FlatW_back));

            gotoxy(8.5, 5);
            printf("                                ");
            gotoxy(10, 6);
            printf("         ");

            FlatBack = 0;

            GameInfo->RequestBack = (x2 == 10) ? 0 : 1;

            GameInfo->NumOfRequest[GameInfo->RequestBack]++;

            PasteInfo(GameInfo, copy);
            CopyTime(GameInfo);
            PrintInfo(GameInfo);
        }

        //-------------------------------------------------------------------

        else if (movement == '\r' && GameInfo->pieces[GameInfo->x][GameInfo->y] == 'o')
        {
            if (GameInfo->turn == 'B')
            {
                if (GameInfo->MODE)
                {
                    FlatB_back = 1;
                    FlatBack = 1;
                    CopyInfo(GameInfo, copy);
                }

                GameInfo->pieces[GameInfo->x][GameInfo->y] = 'B';
                GameInfo->turn = 'W';
            }
            else if (GameInfo->turn == 'W')
            {
                if (GameInfo->MODE)
                {
                    FlatW_back = 1;
                    FlatBack = 1;
                    CopyInfo(GameInfo, copy);
                }

                GameInfo->pieces[GameInfo->x][GameInfo->y] = 'W';
                GameInfo->turn = 'B';
            }

            int ScoreMove = RotatePieces_Score(GameInfo->pieces, GameInfo->x, GameInfo->y);
            GameInfo->score[(GameInfo->turn == 'B') ? 1 : 0] += ScoreMove;

            GameInfo->NumOfPieces[(GameInfo->turn == 'B') ? 1 : 0] += ScoreMove + 1;
            GameInfo->NumOfPieces[(GameInfo->turn == 'B') ? 0 : 1] -= ScoreMove;

            LegalMoves(GameInfo->pieces, GameInfo->turn);

            if (GameInfo->MODE)
            {
                CopyTime(GameInfo);
            }

            if (CheckTurn(GameInfo->pieces, GameInfo->turn))
            {
                PrintInfo(GameInfo);
            }
            else
            {
                GameInfo->turn = (GameInfo->turn == 'B') ? 'W' : 'B';

                LegalMoves(GameInfo->pieces, GameInfo->turn);

                PrintInfo(GameInfo);

                if (!CheckTurn(GameInfo->pieces, GameInfo->turn))
                {
                    char winer = (GameInfo->NumOfPieces[0] > GameInfo->NumOfPieces[1]) ? 'B' : 'W';

                    char NameWiner[40];
                    strcpy(NameWiner, (winer == 'B') ? GameInfo->NamePlayer[0] : GameInfo->NamePlayer[1]);

                    gotoxy(11, 4);
                    printf("Winer is %c ' %s '", winer, NameWiner);
                    char movement1;
                    do
                    {
                        movement1 = getch();

                    } while (movement1 != Esc);

                    return End;
                }
            }
        }

        //-------------------------------------------------------------------

        else if (movement == Esc)
        {
            clear();
            return Unfinished;
        }

    } while (1);
}