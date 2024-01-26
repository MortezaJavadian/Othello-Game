#include "GamePlay.h"

void ToJson(info GameInfo, char FileName[])
{
    FILE *file = fopen(FileName, "r");
    int counter_struct = 1;
    char character = fgetc(file);
    while (character != EOF)
    {
        character = fgetc(file);
        if (character == '\"' || character == (char)(148))
        {
            character = fgetc(file);
            if (character == 'S' || character == (char)(31))
            {
                character = fgetc(file);
                if (character == 't' || character == (char)(250))
                {
                    counter_struct++;
                }
            }
        }
    }
    fclose(file);
    file = fopen(FileName, "a+");

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fprintf(file, "{\n");
    }
    else
    {
        fclose(file);
        file = fopen(FileName, "r+");
        fseek(file, -2, SEEK_END);
        fprintf(file, ",\n\n");
        fclose(file);

        file = fopen(FileName, "a+");
    }
    fprintf(file, "\"Struct_%d\":\n{\n", counter_struct);
    fprintf(file, "\"Type Of Struct\": \"%s\",\n", GameInfo.TypeStruct);
    fprintf(file, "\"Name Player 1\": \"%s\", \"Name Player 2\": \"%s\",\n", GameInfo.NamePlayer[0], GameInfo.NamePlayer[1]);
    fprintf(file, "\"Number Of pieces 1\": \"%d\", \"Number Of pieces 2\": \"%d\",\n", GameInfo.NumOfPieces[0], GameInfo.NumOfPieces[1]);
    fprintf(file, "\"Score 1\": \"%d\", \"Score 2\": \"%d\",\n", GameInfo.score[0], GameInfo.score[1]);
    fprintf(file, "\"Board Pieces\":(\n");

    fprintf(file, "\"+-----------------+\"\n");
    for (int i = 0; i < 8; i++)
    {
        fprintf(file, "\"| ");
        for (int j = 0; j < 8; j++)
        {
            fprintf(file, "%c ", GameInfo.pieces[j][i]);
        }
        fprintf(file, "|\"\n");
    }
    fprintf(file, "\"+-----------------+\"),\n");

    fprintf(file, "\"Turn\": \"%c\",\n", GameInfo.turn);
    fprintf(file, "\"X\": \"%d\", \"Y\": \"%d\",\n", GameInfo.x, GameInfo.y);
    fprintf(file, "\"Mode\": \"%lf\"", GameInfo.MODE);

    if (GameInfo.MODE)
    {
        fprintf(file, ",\n\"Minutes 1\": \"%d\", \"Minutes 2\": \"%d\",\n", GameInfo.minutes[0], GameInfo.minutes[1]);
        fprintf(file, "\"Seconds 1\": \"%lf\", \"Seconds 2\": \"%lf\",\n", GameInfo.seconds[0], GameInfo.seconds[1]);
        fprintf(file, "\"Request Back Player\": \"%d\",\n", GameInfo.RequestBack);
        fprintf(file, "\"Number Of Request 1\": \"%d\", \"Number Of Request 2\": \"%d\",\n", GameInfo.NumOfRequest[0], GameInfo.NumOfRequest[1]);
        fprintf(file, "\"Temp Time 1\"=> \"Minutes1\": \"%lf\", \"Seconds1\": \"%lf\",\n", GameInfo.TempTime[0][0], GameInfo.TempTime[0][1]);
        fprintf(file, "\"Temp Time 2\"=> \"Minutes2\": \"%lf\", \"Seconds2\": \"%lf\"\n}\n}", GameInfo.TempTime[1][0], GameInfo.TempTime[1][1]);
    }
    else
    {
        fprintf(file, "\n}\n}");
    }

    fclose(file);
}

void FromJson(FILE *file, info *GameInfo)
{
    fscanf(file, "%*[^:]%*c%*[^:]%*c%*c%*c%[^\"]", &GameInfo->TypeStruct);
    fscanf(file, "%*[^:]%*c%*c%*c%[^\"]", &GameInfo->NamePlayer[0]);
    fscanf(file, "%*[^:]%*c%*c%*c%[^\"]", &GameInfo->NamePlayer[1]);

    fscanf(file, "%*[^:]%*c%*c%*c%d", &GameInfo->NumOfPieces[0]);
    fscanf(file, "%*[^:]%*c%*c%*c%d", &GameInfo->NumOfPieces[1]);

    fscanf(file, "%*[^:]%*c%*c%*c%d %*[^:]%*c%*c%*c%d", &GameInfo->score[0], &GameInfo->score[1]);

    fscanf(file, "%*[^|]%*c%*c");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fscanf(file, "%c%*c", &GameInfo->pieces[j][i]);
        }
        fscanf(file, "%*c%*c%*c%*c%*c%*c");
    }

    fscanf(file, "%*[^:]%*c%*c%*c%c", &GameInfo->turn);
    fscanf(file, "%*[^:]%*c%*c%*c%d %*[^:]%*c%*c%*c%d", &GameInfo->x, &GameInfo->y);
    fscanf(file, "%*[^:]%*c%*c%*c%lf", &GameInfo->MODE);

    if (GameInfo->MODE)
    {
        fscanf(file, "%*[^:]%*c%*c%*c%d %*[^:]%*c%*c%*c%d", &GameInfo->minutes[0], &GameInfo->minutes[1]);
        fscanf(file, "%*[^:]%*c%*c%*c%lf %*[^:]%*c%*c%*c%lf", &GameInfo->seconds[0], &GameInfo->seconds[1]);
        fscanf(file, "%*[^:]%*c%*c%*c%d", &GameInfo->RequestBack);
        fscanf(file, "%*[^:]%*c%*c%*c%d %*[^:]%*c%*c%*c%d", &GameInfo->NumOfRequest[0], &GameInfo->NumOfRequest[1]);
        fscanf(file, "%*[^:]%*c%*c%*c%lf %*[^:]%*c%*c%*c%lf", &GameInfo->TempTime[0][0], &GameInfo->TempTime[0][1]);
        fscanf(file, "%*[^:]%*c%*c%*c%lf %*[^:]%*c%*c%*c%lf", &GameInfo->TempTime[1][0], &GameInfo->TempTime[1][1]);
    }
}

void ChangeJson(info GameInfo, info copy[2], char FileName[], int TargetGame)
{
    FILE *file = fopen(FileName, "r");
    FILE *TempFile = fopen("temp.json", "w");

    int character = (int)fgetc(file);
    while (character != EOF)
    {
        fprintf(TempFile, "%c", (char)character);
        character = (int)fgetc(file);
    }
    fclose(TempFile);
    fclose(file);

    file = fopen(FileName, "w");
    TempFile = fopen("temp.json", "r");

    info TempGame;
    int i = 0;
    while (i < TargetGame - 1)
    {
        FromJson(TempFile, &TempGame);
        ToJson(TempGame, FileName);
        if (strcmp(TempGame.TypeStruct, "main"))
        {
            continue;
        }
        i++;
    }
    if (TempGame.MODE && i != 0)
    {
        FromJson(TempFile, &TempGame);
        ToJson(TempGame, FileName);
        FromJson(TempFile, &TempGame);
        ToJson(TempGame, FileName);
    }

    FromJson(TempFile, &TempGame);
    if (TempGame.MODE)
    {
        FromJson(TempFile, &TempGame);
        FromJson(TempFile, &TempGame);
    }

    ToJson(GameInfo, FileName);
    if (GameInfo.MODE)
    {
        ToJson(copy[0], FileName);
        ToJson(copy[1], FileName);
    }

    do
    {
        TempGame.TypeStruct[0] = 0;
        FromJson(TempFile, &TempGame);
        if (TempGame.TypeStruct[0] == 0)
        {
            break;
        }

        ToJson(TempGame, FileName);

    } while (1);

    fclose(file);
    fclose(TempFile);
    remove("temp.json");
}