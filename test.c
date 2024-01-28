// #include "GamePlay.h"
// #include "json.h"
// #include "secret.h"

// void PrintGame(info *ListGame, int x)
// {
//     for (int i = x; i < x + 3; i++, i++)
//     {
//         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

//         gotoxy(2.5, 2 * (1.25 * i + 0.25));
//         printf("%d. %s vs %s", i + 1, ListGame[i].NamePlayer[0], ListGame[i].NamePlayer[1]);
//         gotoxy(2.5, 2 * (1.25 * i + 0.25) + 0.5);
//         printf("    Mode: %s", (ListGame[i].MODE == 0) ? "Classic" : "Timer");
//         gotoxy(2.5, 2 * (1.25 * i + 0.25) + 1);
//         printf("    Score %s: %d", ListGame[i].NamePlayer[0], ListGame[i].score[0]);
//         gotoxy(2.5, 2 * (1.25 * i + 0.25) + 1.5);
//         printf("    Score %s: %d", ListGame[i].NamePlayer[1], ListGame[i].score[1]);

//         if (i != x + 2)
//         {
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
//             gotoxy(1.5, 2 * (1.25 * i + 0.25) + 2);
//             printf("-----------------------------");
//         }
//     }
// }

// int UnfinishedGame()
// {
//     PrintBorder();

//     gotoxy(2.5, -1.5);
//     printf("+-----------------+");
//     gotoxy(2.5, -1);
//     printf("| Unfinished Game |");
//     gotoxy(2.5, -0.5);
//     printf("+-----------------+");
//     gotoxy(1, 0.5);

//     char FileName[] = "Unfinished.json";
//     FILE *file = fopen(FileName, "r");

//     FromSecret(file, FileName);
//     fclose(file);

//     file = fopen(FileName, "r");

//     int counter_game = 0;
//     info *ListGame = (info *)malloc(sizeof(info));
//     do
//     {
//         info MainGame;
//         MainGame.TypeStruct[0] = 0;
//         FromJson(file, &MainGame);
//         if (MainGame.TypeStruct[0] == 0)
//         {
//             break;
//         }
//         else if (strcmp(MainGame.TypeStruct, "main"))
//         {
//             continue;
//         }
//         counter_game++;
//         ListGame = (info *)realloc(ListGame, counter_game * sizeof(info));

//         strcpy(ListGame[counter_game - 1].NamePlayer[0], MainGame.NamePlayer[0]);
//         strcpy(ListGame[counter_game - 1].NamePlayer[1], MainGame.NamePlayer[1]);

//         ListGame[counter_game - 1].MODE = MainGame.MODE;
//         ListGame[counter_game - 1].score[0] = MainGame.score[0];
//         ListGame[counter_game - 1].score[1] = MainGame.score[1];

//     } while (1);
//     fclose(file);

//     double y = 0.5;
//     int flat = 1;
//     int x = 0;
//     char movement;
//     do
//     {
//         if (flat)
//         {
//             PrintGame(ListGame, x);
//             flat = 0;
//         }
//         gotoxy(2.5, y);
//         movement = getch();

//         if (movement == Down && y < 5.5)
//         {
//             gotoxy(2.5, y += 2.5);
//         }
//         else if (movement == Down && y == 5.5 && x + 3 < counter_game)
//         {
//             x++;
//             flat = 1;
//         }
//         else if (movement == Up && 0.5 < y)
//         {
//             gotoxy(2.5, y -= 2.5);
//         }
//         else if (movement == Up && 0.5 == y && 0 < x)
//         {
//             x--;
//             flat = 1;
//         }
//         else if (movement == Esc)
//         {
//             file = fopen(FileName, "r");
//             ToSecret(file, FileName);
//             fclose(file);
//             return 0;
//         }

//     } while (movement != '\r');

//     int TargetGame = ((y + 3.5) / 2) + x;
//     file = fopen(FileName, "r");

//     info GameInfo;
//     info copy[2];
//     int i = 0;
//     while (i < TargetGame)
//     {
//         FromJson(file, &GameInfo);
//         if (strcmp(GameInfo.TypeStruct, "main"))
//         {
//             continue;
//         }
//         i++;
//     }

//     if (GameInfo.MODE)
//     {
//         FromJson(file, &copy[0]);
//         FromJson(file, &copy[1]);
//     }

//     fclose(file);

//     int mode = GameBackground(&GameInfo, copy);

//     if (mode == End)
//     {
//         RemoveJson(FileName, TargetGame);
//         char name[] = "Score.json";
//         ToJson(GameInfo, name);

//         FILE *SaveFile = fopen(name, "r");
//         ToSecret(SaveFile, name);
//         fclose(SaveFile);
//     }
//     else if (mode == Unfinished)
//     {
//         ChangeJson(GameInfo, copy, FileName, TargetGame);
//     }

//     file = fopen(FileName, "r");
//     ToSecret(file, FileName);
//     fclose(file);
//     return 0;
// }