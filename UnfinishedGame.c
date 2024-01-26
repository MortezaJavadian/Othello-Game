#include "GamePlay.h"
#include "json.h"
#include "secret.h"

int UnfinishedGame()
{
    char FileName[] = "Unfinished.json";
    FILE *file = fopen(FileName, "r");

    FromSecret(file, FileName);
    fclose(file);

    file = fopen(FileName, "r");
    double counter_game = 0;
    do
    {
        info MainGame;
        MainGame.TypeStruct[0] = 0;
        FromJson(file, &MainGame);
        if (MainGame.TypeStruct[0] == 0)
        {
            break;
        }
        else if (strcmp(MainGame.TypeStruct, "main"))
        {
            continue;
        }
        counter_game++;

        gotoxy(2.5, 2 * (counter_game - 1.75));
        printf("%d. %s vs %s", (int)counter_game, MainGame.NamePlayer[0], MainGame.NamePlayer[1]);
        gotoxy(2.5, 2 * (counter_game - 1.75) + 0.5);
        printf("    Mode: %s", (MainGame.MODE == 0) ? "Classic" : "Timer");
        gotoxy(2.5, 2 * (counter_game - 1.75) + 1);
        printf("    Score %s: %d", MainGame.NamePlayer[0], MainGame.score[0]);
        gotoxy(2.5, 2 * (counter_game - 1.75) + 1.5);
        printf("    Score %s: %d", MainGame.NamePlayer[1], MainGame.score[1]);

    } while (1);
    fclose(file);

    double y = -1.5;
    gotoxy(2.5, y);
    char movement;
    do
    {
        movement = getch();

        if (movement == Down && y < 2 * (counter_game - 1.75))
        {
            gotoxy(2.5, y += 2);
        }
        else if (movement == Up && -1.5 < y)
        {
            gotoxy(2.5, y -= 2);
        }
        else if (movement == Esc)
        {
            file = fopen(FileName, "r");
            ToSecret(file, FileName);
            fclose(file);
            return 0;
        }

    } while (movement != '\r');

    int TargetGame = (y + 3.5) / 2;
    file = fopen(FileName, "r");

    info GameInfo;
    info copy[2];
    int i = 0;
    while (i < TargetGame)
    {
        FromJson(file, &GameInfo);
        if (strcmp(GameInfo.TypeStruct, "main"))
        {
            continue;
        }
        i++;
    }

    if (GameInfo.MODE)
    {
        FromJson(file, &copy[0]);
        FromJson(file, &copy[1]);
    }

    fclose(file);

    int mode = GameBackground(&GameInfo, copy);

    if (mode == End)
    {
        RemoveJson(FileName, TargetGame);
    }
    else if (mode == Unfinished)
    {
        ChangeJson(GameInfo, copy, FileName, TargetGame);
    }

    file = fopen(FileName, "r");
    ToSecret(file, FileName);
    fclose(file);
    return 0;
}