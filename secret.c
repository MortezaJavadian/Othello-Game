#include "GamePlay.h"

#define a 4025211
#define b 62

void ToSecret(FILE *file)
{
    FILE *temp = fopen("temp.json", "w");

    int character = (int)fgetc(file);
    while (character != EOF)
    {
        fprintf(temp, "%c", (char)character);
        character = (int)fgetc(file);
    }
    fclose(temp);
    fclose(file);

    file = fopen("save.json", "w");
    temp = fopen("temp.json", "r");

    character = (int)fgetc(temp);
    while (character != EOF)
    {
        character = (a * character + b) % 256;
        fprintf(file, "%c", (char)character);

        character = (int)fgetc(temp);
    }

    fclose(temp);
    remove("temp.json");
}

void FromSecret(FILE *file)
{
    FILE *temp = fopen("temp.json", "w");

    int character = (int)fgetc(file);
    while (character != EOF)
    {
        fprintf(temp, "%c", (char)character);
        character = (int)fgetc(file);
    }
    fclose(temp);
    fclose(file);

    file = fopen("save.json", "w");
    temp = fopen("temp.json", "r");

    character = (int)fgetc(temp);
    while (character != EOF)
    {
        int i = 0;
        while (((character - b) + i * 256) % a != 0)
        {
            i++;
        }
        character = (((character - b) + i * 256) / a) % 256;
        fprintf(file, "%c", (char)character);
        character = (int)fgetc(temp);
    }

    fclose(temp);
    remove("temp.json");
}