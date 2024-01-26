#include "GamePlay.h"

#define a 3
#define b 7

void ToSecret(FILE *file, char NameFile[])
{
    FILE *temp = fopen("temp.json", "w");

    char character = fgetc(file);
    while (character != EOF)
    {
        fprintf(temp, "%c", character);
        character = fgetc(file);
    }
    fclose(temp);
    fclose(file);

    file = fopen(NameFile, "w");
    temp = fopen("temp.json", "r");

    int flat1 = 1;
    int flat2 = 0;
    character = fgetc(temp);
    while (character != EOF)
    {
        fprintf(file, "%c", character);
        character = fgetc(temp);
        if (character == ',')
        {
            fprintf(file, "%c", character);
            character = fgetc(temp);
            if (character == '\n')
            {
                fprintf(file, "%c", character);
                character = fgetc(temp);
                if (character == '\n')
                {
                    fprintf(file, "%c", character);
                    character = fgetc(temp);
                    if (character == '\"')
                    {
                        fprintf(file, "%c", character);

                        fseek(file, -6, SEEK_CUR);
                        fseek(temp, -6, SEEK_CUR);
                        flat1 = 0;
                        break;
                    }
                }
            }
        }
        else if (character == '\n')
        {
            fprintf(file, "%c", character);
            character = fgetc(temp);
            if (character == '\"')
            {
                fprintf(file, "%c", character);
                character = fgetc(temp);
                if (character == 'S')
                {
                    flat2 = 1;
                    break;
                }
            }
        }
    }
    if (flat1 && flat2)
    {
        fclose(file);
        file = fopen(NameFile, "w");
        fseek(temp, 0, SEEK_SET);
    }

    character = fgetc(temp);
    while (character != EOF)
    {
        character = (a * character + b) % 256;
        fprintf(file, "%c", (char)character);

        character = fgetc(temp);
    }

    fclose(temp);
    remove("temp.json");
}

void FromSecret(FILE *file, char NameFile[])
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

    file = fopen(NameFile, "w");
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