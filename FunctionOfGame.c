#include "GamePlay.h"

void clear()
{
    system("cls");
}

void gotoxy(double x, double y)
{
    COORD coord;
    coord.X = 4 * x + 44;
    coord.Y = 2 * y + 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void PrintBoard()
{
    clear();

    printf("\n\n\n");
    printf("\t\t\t\t\t    A   B   C   D   E   F   G   H  \n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t1 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t2 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t3 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t4 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t5 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t6 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t7 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n"
           "\t\t\t\t\t8 |   |   |   |   |   |   |   |   |\n"
           "\t\t\t\t\t  +---+---+---+---+---+---+---+---+\n");
}

int RotatePieces_Score(char pieces[8][8], int j, int i)
{
    int score = 0;

    char turn = pieces[j][i];
    char opponent = (turn == 'B') ? 'W' : 'B';

    int row = 1;
    int column = 1;
    for (int k = 0; k < 8; k++)
    {
        int x = j;
        int y = i;
        int temp = 0;
        do
        {
            x += row;
            y += column;
            temp++;

        } while (pieces[x][y] == opponent && 0 <= x && x <= 7 && 0 <= y && y <= 7);

        if (pieces[x][y] == turn && temp != 1 && 0 <= x && x <= 7 && 0 <= y && y <= 7)
        {
            x -= row;
            y -= column;
            do
            {
                pieces[x][y] = turn;
                score++;
                x -= row;
                y -= column;

            } while (pieces[x][y] == opponent);
        }

        if (k < 2)
        {
            row--;
        }
        else if (k < 4)
        {
            column--;
        }
        else if (k < 6)
        {
            row++;
        }
        else
        {
            column++;
        }
    }

    return score;
}

void LegalMoves(char pieces[8][8], char turn)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieces[j][i] == 'o')
            {
                pieces[j][i] = ' ';
            }
        }
    }
    char opponent = (turn == 'B') ? 'W' : 'B';
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieces[j][i] == turn)
            {
                int row = 1;
                int column = 1;

                for (int k = 0; k < 8; k++)
                {
                    int x = j;
                    int y = i;
                    int temp = 0;
                    do
                    {
                        x += row;
                        y += column;
                        temp++;

                    } while (pieces[x][y] == opponent && 0 <= x && x <= 7 && 0 <= y && y <= 7);

                    if (pieces[x][y] != turn && temp != 1 && 0 <= x && x <= 7 && 0 <= y && y <= 7)
                    {
                        pieces[x][y] = 'o';
                    }

                    if (k < 2)
                    {
                        row--;
                    }
                    else if (k < 4)
                    {
                        column--;
                    }
                    else if (k < 6)
                    {
                        row++;
                    }
                    else
                    {
                        column++;
                    }
                }
            }
        }
    }
}

void PrintInfo(info *GameInfo)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gotoxy(j, i);
            if (GameInfo->pieces[j][i] == 'B')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
                printf("%c", GameInfo->pieces[j][i]);
            }
            else if (GameInfo->pieces[j][i] == 'W')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("%c", GameInfo->pieces[j][i]);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                printf("%c", GameInfo->pieces[j][i]);
            }
        }
    }

    gotoxy(11, -1);
    printf("Turn %c", GameInfo->turn);

    gotoxy(11, 0);
    printf("B : %d ", GameInfo->NumOfPieces[0]);
    gotoxy(11, 1);
    printf("W : %d ", GameInfo->NumOfPieces[1]);

    if (GameInfo->MODE)
    {
        gotoxy(11, 2);
        printf("B : %.2d : %.2d", GameInfo->minutes[0], (int)GameInfo->seconds[0]);

        gotoxy(11, 3);
        printf("W : %.2d : %.2d", GameInfo->minutes[1], (int)GameInfo->seconds[1]);
    }

    gotoxy(GameInfo->x, GameInfo->y);
}

int CheckTurn(char pieces[8][8], char turn)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieces[j][i] == 'o')
            {
                return 1;
            }
        }
    }
    return 0;
}

void timer(info *GameInfo)
{
    int turn = (GameInfo->turn == 'B') ? 0 : 1;
    do
    {
        gotoxy(12, turn + 2);
        printf("%.2d : %.2d", GameInfo->minutes[turn], (int)GameInfo->seconds[turn]);
        gotoxy(GameInfo->x, GameInfo->y);

        if (GameInfo->seconds[turn] <= 0)
        {
            GameInfo->minutes[turn]--;
            GameInfo->seconds[turn] += 60;
        }

        GameInfo->seconds[turn] -= 0.05;
        Sleep(40);

    } while (!kbhit() && (GameInfo->minutes[turn] > 0 || GameInfo->seconds[turn] > 0));
}

void CopyInfo(info *GameInfo, info copy[2])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            copy[(GameInfo->turn == 'B') ? 0 : 1].pieces[j][i] = GameInfo->pieces[j][i];
        }
    }

    copy[(GameInfo->turn == 'B') ? 0 : 1].x = GameInfo->x;
    copy[(GameInfo->turn == 'B') ? 0 : 1].y = GameInfo->y;

    copy[(GameInfo->turn == 'B') ? 0 : 1].turn = GameInfo->turn;
    copy[(GameInfo->turn == 'B') ? 0 : 1].MODE = GameInfo->MODE;

    for (int i = 0; i < 2; i++)
    {
        copy[(GameInfo->turn == 'B') ? 0 : 1].NumOfPieces[i] = GameInfo->NumOfPieces[i];
        copy[(GameInfo->turn == 'B') ? 0 : 1].score[i] = GameInfo->score[i];

        copy[(GameInfo->turn == 'B') ? 0 : 1].minutes[i] = GameInfo->TempTime[i][0];
        copy[(GameInfo->turn == 'B') ? 0 : 1].seconds[i] = GameInfo->TempTime[i][1];
    }
}

void CopyTime(info *GameInfo)
{
    for (int i = 0; i < 2; i++)
    {
        GameInfo->TempTime[i][0] = (double)GameInfo->minutes[i];
        GameInfo->TempTime[i][1] = GameInfo->seconds[i];
    }
}

void PasteInfo(info *GameInfo, info copy[2])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            GameInfo->pieces[j][i] = copy[GameInfo->RequestBack].pieces[j][i];
        }
    }

    GameInfo->x = copy[GameInfo->RequestBack].x;
    GameInfo->y = copy[GameInfo->RequestBack].y;

    GameInfo->turn = copy[GameInfo->RequestBack].turn;

    int DiffMinutes[2];
    double DiffSeconds[2];
    for (int i = 0; i < 2; i++)
    {
        if (GameInfo->NumOfRequest[GameInfo->RequestBack] == 2)
        {
            if (GameInfo->seconds[i] <= copy[GameInfo->RequestBack].seconds[i])
            {
                DiffMinutes[i] = copy[GameInfo->RequestBack].minutes[i] - GameInfo->minutes[i];
                DiffSeconds[i] = copy[GameInfo->RequestBack].seconds[i] - GameInfo->seconds[i];
            }
            else
            {
                copy[GameInfo->RequestBack].minutes[i]--;
                copy[GameInfo->RequestBack].seconds[i] += 60;

                DiffMinutes[i] = copy[GameInfo->RequestBack].minutes[i] - GameInfo->minutes[i];
                DiffSeconds[i] = copy[GameInfo->RequestBack].seconds[i] - GameInfo->seconds[i];
            }
        }

        GameInfo->NumOfPieces[i] = copy[GameInfo->RequestBack].NumOfPieces[i];
        GameInfo->score[i] = copy[GameInfo->RequestBack].score[i];
        GameInfo->minutes[i] = copy[GameInfo->RequestBack].minutes[i];
        GameInfo->seconds[i] = copy[GameInfo->RequestBack].seconds[i];
    }

    if (GameInfo->NumOfRequest[GameInfo->RequestBack] == 1)
    {
        if (GameInfo->seconds[GameInfo->RequestBack] >= 30)
        {
            GameInfo->seconds[GameInfo->RequestBack] -= 30;
        }
        else
        {
            if (GameInfo->minutes[GameInfo->RequestBack] >= 1)
            {
                GameInfo->minutes[GameInfo->RequestBack]--;
                GameInfo->seconds[GameInfo->RequestBack] += 30;
            }
            else
            {
                GameInfo->seconds[GameInfo->RequestBack] = 0;
            }
        }
    }
    else if (GameInfo->NumOfRequest[GameInfo->RequestBack] == 2)
    {
        if (GameInfo->minutes[GameInfo->RequestBack] >= 1)
        {
            GameInfo->minutes[GameInfo->RequestBack]--;
        }
        else
        {
            GameInfo->seconds[GameInfo->RequestBack] = 0;
        }

        GameInfo->seconds[!(GameInfo->RequestBack)] += (DiffSeconds[0] + DiffSeconds[1]);
        GameInfo->minutes[!(GameInfo->RequestBack)] += (DiffMinutes[0] + DiffMinutes[1]);

        if (GameInfo->seconds[!(GameInfo->RequestBack)] >= 60)
        {
            GameInfo->seconds[!(GameInfo->RequestBack)] -= 60;
            GameInfo->minutes[!(GameInfo->RequestBack)]++;
        }
    }
}