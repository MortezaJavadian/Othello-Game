#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define Up 72
#define Down 80
#define Left 75
#define Right 77
#define Esc 27
#define Backspace 8

#define End 0
#define Unfinished 1

struct GameInfo
{
    char TypeStruct[7];
    char NamePlayer[2][40];
    char pieces[8][8];
    int x;
    int y;
    char turn;
    int NumOfPieces[2];
    int score[2];
    double MODE;
    int minutes[2];
    double seconds[2];
    int RequestBack;
    int NumOfRequest[2];
    double TempTime[2][2];
};

typedef struct GameInfo info;

void clear();

void gotoxy(double x, double y);

void PrintBorder();

void PrintBoard();

int RotatePieces_Score(char pieces[8][8], int j, int i);

void LegalMoves(char pieces[8][8], char turn);

void PrintInfo(info *GameInfo);

int CheckTurn(char pieces[8][8], char turn);

void timer(info *GameInfo);

void CopyInfo(info *GameInfo, info copy[2]);

void CopyTime(info *GameInfo);

void PasteInfo(info *GameInfo, info copy[2]);



int HomePage();

int NewGame();

int GameBackground(info *GameInfo, info copy[2]);

int UnfinishedGame();

void Score();