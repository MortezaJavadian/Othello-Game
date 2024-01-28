#include "GamePlay.h"
#include "secret.h"
#include "json.h"

struct ScorePlayer
{
    char NamePlayer[40];
    int TotalScore;
};

typedef struct ScorePlayer SCORE;

void Score()
{
    char FileName[] = "Score.json";
    FILE *file = fopen(FileName, "r");
    FromSecret(file, FileName);
    fclose(file);

    file = fopen(FileName, "r");
    int CounterPlayer = 0;
    SCORE *score = (SCORE *)malloc(sizeof(SCORE));
    do
    {
        info GameInfo;
        GameInfo.TypeStruct[0] = 0;
        FromJson(file, &GameInfo);
        if (GameInfo.TypeStruct[0] == 0)
        {
            break;
        }

        if (CounterPlayer == 0)
        {
            CounterPlayer += 2;
            score = (SCORE *)realloc(score, CounterPlayer * sizeof(SCORE));
            score[0].TotalScore = GameInfo.score[0];
            score[1].TotalScore = GameInfo.score[1];

            strcpy(score[0].NamePlayer, GameInfo.NamePlayer[0]);
            strcpy(score[1].NamePlayer, GameInfo.NamePlayer[1]);
        }
        else
        {
            int check = 1;
            for (int i = 0; i < CounterPlayer; i++)
            {
                if (strcmp(score[i].NamePlayer, GameInfo.NamePlayer[0]) == 0)
                {
                    score[i].TotalScore += GameInfo.score[0];
                    check = 0;
                    break;
                }
            }
            if (check)
            {
                CounterPlayer++;
                score = (SCORE *)realloc(score, CounterPlayer * sizeof(SCORE));

                score[CounterPlayer - 1].TotalScore = GameInfo.score[0];
                strcpy(score[CounterPlayer - 1].NamePlayer, GameInfo.NamePlayer[0]);
            }

            check = 1;
            for (int i = 0; i < CounterPlayer; i++)
            {
                if (strcmp(score[i].NamePlayer, GameInfo.NamePlayer[1]) == 0)
                {
                    score[i].TotalScore += GameInfo.score[1];
                    check = 0;
                    break;
                }
            }
            if (check)
            {
                CounterPlayer++;
                score = (SCORE *)realloc(score, CounterPlayer * sizeof(SCORE));

                score[CounterPlayer - 1].TotalScore = GameInfo.score[1];
                strcpy(score[CounterPlayer - 1].NamePlayer, GameInfo.NamePlayer[1]);
            }
        }

    } while (1);
    fclose(file);

    file = fopen(FileName, "r");
    ToSecret(file, FileName);
    fclose(file);

    for (int i = 0; i < CounterPlayer; i++)
    {
        for (int j = i + 1; j < CounterPlayer; j++)
        {
            if (score[i].TotalScore < score[j].TotalScore)
            {
                int temp = score[i].TotalScore;
                score[i].TotalScore = score[j].TotalScore;
                score[j].TotalScore = temp;

                char TempName[40];
                strcpy(TempName, score[i].NamePlayer);
                strcpy(score[i].NamePlayer, score[j].NamePlayer);
                strcpy(score[j].NamePlayer, TempName);
            }
        }
    }
    
    PrintBorder();

    gotoxy(2.5, -1.5);
    printf("+--------------+");
    gotoxy(2.5, -1);
    printf("| Game Ranking |");
    gotoxy(2.5, -0.5);
    printf("+--------------+");
    gotoxy(1, 0.5);
    printf("Player Name\t\tScore");
    for (int i = 0; i < CounterPlayer; i++)
    {
        gotoxy(1, 1.5 + i / 2.0);
        printf("%d.%s", i + 1, score[i].NamePlayer);
        gotoxy(7.5, 1.5 + i / 2.0);
        printf("%d", score[i].TotalScore);
    }

    char movement1;
    do
    {
        movement1 = getch();

    } while (movement1 != Esc);
}