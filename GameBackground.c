#include "GamePlay.h"

int GameBackground(info *GameInfo, info copy[2])
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    //-------------------------------------------------------------------

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
                gotoxy(11, 4);
                printf("Winer is W ' %s '", GameInfo->NamePlayer[1]);
                gotoxy(0, 8);
                return End;
            }
            else if (GameInfo->minutes[1] <= 0 && GameInfo->seconds[1] <= 0)
            {
                gotoxy(11, 4);
                printf("Winer is B ' %s '", GameInfo->NamePlayer[0]);
                gotoxy(0, 8);
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

        else if (GameInfo->MODE && (movement == Backspace) && (GameInfo->NumOfRequest[0] != 2 || GameInfo->NumOfRequest[1] != 2))
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

            } while (movement2 != '\r' || GameInfo->NumOfRequest[(x2 == 11) ? 0 : 1] == 2);

            gotoxy(11, 5);
            printf("                                ");
            gotoxy(11, 6);
            printf("         ");

            GameInfo->RequestBack = (x2 == 11) ? 0 : 1;

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
                    CopyInfo(GameInfo, copy);
                }

                GameInfo->pieces[GameInfo->x][GameInfo->y] = 'B';
                GameInfo->turn = 'W';
            }
            else if (GameInfo->turn == 'W')
            {
                if (GameInfo->MODE)
                {
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