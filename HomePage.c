#include "GamePlay.h"


int HomePage()
{
       clear();
       system("title Othello");

       PrintBorder();

       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
       printf("\n\n");
       printf("\t\t\t\t #######  ##########  ##      ##  ########  ##        ##        ####### \n"
              "\t\t\t\t##     ##     ##      ##      ##  ##        ##        ##       ##     ##\n"
              "\t\t\t\t##     ##     ##      ##      ##  ##        ##        ##       ##     ##\n"
              "\t\t\t\t##     ##     ##      ##########  ######    ##        ##       ##     ##\n"
              "\t\t\t\t##     ##     ##      ##      ##  ##        ##        ##       ##     ##\n"
              "\t\t\t\t##     ##     ##      ##      ##  ##        ##        ##       ##     ##\n"
              "\t\t\t\t #######      ##      ##      ##  ########  ########  ########  ####### \n\n");

       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
       printf("\t\t\t\t\t\t\t    1.New Game\n"
              "\t\t\t\t\t\t\t    2.Unfinished Games\n"
              "\t\t\t\t\t\t\t    3.Score List\n"
              "\t\t\t\t\t\t\t    4.Exit");

       double y = 3;
       gotoxy(4, y);
       char movement;
       do
       {
              movement = getch();

              if (movement == Down && y < 4.5)
              {
                     gotoxy(4, y += 0.5);
              }
              else if (movement == Down && y == 4.5)
              {
                     gotoxy(4, y -= 1.5);
              }
              else if (movement == Up && 3 < y)
              {
                     gotoxy(4, y -= 0.5);
              }
              else if (movement == Up && 3 == y)
              {
                     gotoxy(4, y += 1.5);
              }
              else if (movement == Esc)
              {
                     clear();
                     return 4;
              }

       } while (movement != '\r');
       clear();

       return 2 * y - 5;
}