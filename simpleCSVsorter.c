#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "simpleCSVsorter.h"


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    // create array that holds 10 movieRecord pointers (10 pointers that each point to a movieRecord)
    struct MovieRecord *arrayOfMovies[MAX_NUM_RECORDS];

    for (int i = 0; i < MAX_NUM_RECORDS+1; i++)
    {
        arrayOfMovies[i] = malloc(sizeof(struct MovieRecord));
    }
   
    /*** get input from csv via stdin ***/
    int numberOfMovieRecords = 0;
    char line[MAX_LINE_LENGTH];
    char **arrayOfTokens = malloc(sizeof(char *) * MAX_NUM_COLUMNS);

    if (arrayOfTokens == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrayOfTokens");
        return -1;
    }

    int count = 0;
    while (getLine(line, MAX_LINE_LENGTH) != EOF)
    {
        getArrayOfTokens(arrayOfTokens, line, DELIMITER);

        char *colorString = arrayOfTokens[0];
        char *animalString = arrayOfTokens[2];

        arrayOfMovies[count]->color = malloc(sizeof(char) * strlen(colorString));
        strcpy(arrayOfMovies[count]->color, colorString);

        arrayOfMovies[count]->number = atoi(arrayOfTokens[1]);

        arrayOfMovies[count]->animal = malloc(sizeof(char) * strlen(animalString));
        strcpy(arrayOfMovies[count]->animal, animalString);

        count++;
    }

    printMovieRecords(arrayOfMovies, count);

    return 0;
}

void printArguments(int argCount, char *argArray[])
{
    printf("%s Number of Arguments: %d\n", DEBUGGING, argCount);

    for (int i = 0; i < argCount; i++)
    {
        printf("%s Argument %d: %s\n", DEBUGGING, i, argArray[i]);
    }

    return;
}

void getArrayOfTokens(char **arrayOfTokens, char *line, const char *delimiter)
{
    // declare char[] to hold each token string as it is processed and assign first string returned from strtok
    char *stringToken = strtok(line, delimiter); 

    int i = 0;

    while (stringToken != NULL)
    {
        arrayOfTokens[i] = (char *)malloc(sizeof(strlen(stringToken)+1)*sizeof(char));
        strcpy(arrayOfTokens[i], stringToken);
        stringToken = strtok(NULL, delimiter);
        i++;
    }

    return;
}

void printMovieRecords(struct MovieRecord **arrayOfMovieRecords, int lengthOfArrayOfMovieRecords)
{

    struct MovieRecord **tempArrayOfMovieRecords = arrayOfMovieRecords;
    for (int i = 0; i < lengthOfArrayOfMovieRecords; i++)
    {
        printf("%s,%d,%s\n", tempArrayOfMovieRecords[i]->color, tempArrayOfMovieRecords[i]->number, tempArrayOfMovieRecords[i]->animal);
    }

    return;
}

int getLine(char line[], int maxLength)
{
    int index = 0;
    int aChar;
    // want to leave space for '\0'
    int maxStringLength = maxLength - 1;

    while ((aChar = getchar()) != EOF)
    {
        if (aChar == '\n')
        {
            break;
        }

        if (index < maxStringLength)
        {
            line[index] = aChar;
            index++;
        }
    }

    if (aChar == EOF && (index == 0))
    {
        return EOF;
    }

    line[index] = '\0';

    return index;
}
