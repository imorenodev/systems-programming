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

    // initialize each MovieRecord pointer to point to an allocated block of memory to hold a struct MovieRecord
    initializeArrayOfMovies(MAX_NUM_RECORDS, arrayOfMovies);
   
    /*** get input from csv via stdin ***/
    int numberOfMovieRecords = 0;
    char line[MAX_LINE_LENGTH];
    char **arrayOfTokens = malloc(sizeof(char *) * MAX_NUM_COLUMNS);

    if (arrayOfTokens == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrayOfTokens");
        return -1;
    }

    // process stdin line by line.
    // tokenize the line.
    // save tokens in each struct MovieRecord's corresponding members.
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

    // create new array of pointers to struct MovieRecords to hold accurate number of MoveRecords
    struct MovieRecord *unSortedArrayOfMovies[count];
    initializeArrayOfMovies(count, unSortedArrayOfMovies);
    // copy contents of oversized array of MovieRecords to new array of correct size
    copyArrayOfMovies(count, arrayOfMovies, unSortedArrayOfMovies);

    printf("\n** COPIED arrayOfMovies into unSortedArrayOfMovies **\n");
    printMovieRecords(count, unSortedArrayOfMovies);
    printf("\n** SUCCESSFULLY COPIED arrayOfMovies into unSortedArrayOfMovies **\n");

    // create new array of pointers to struct MovieRecords to hold sorted MovieRecords
    struct MovieRecord *sortedArrayOfMovies[count];
    initializeArrayOfMovies(count, sortedArrayOfMovies);

    // sort the records and save sorted output in sortedArrayOfMovies
    //mergeSort(count, arrayOfMovies, sortedArrayOfMovies);

    printMovieRecords(count, arrayOfMovies);

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

void printMovieRecords(int count, struct MovieRecord **arrayOfMovieRecords)
{

    struct MovieRecord **tempArrayOfMovieRecords = arrayOfMovieRecords;
    for (int i = 0; i < count; i++)
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

void initializeArrayOfMovies(int numberOfRecords, struct MovieRecord **arrayOfMovies)
{
    for (int i = 0; i < numberOfRecords; i++)
    {
        arrayOfMovies[i] = malloc(sizeof(struct MovieRecord));
    }

    return;
}

void copyArrayOfMovies(int count, struct MovieRecord **overSizedArray, struct MovieRecord **correctSizeArray)
{
    for (int i = 0; i < count; i++)
    {
        // grab temporary strings from overSizedArray so we can count the length for malloc initialization
        char *colorString = overSizedArray[i]->color;
        char *animalString = overSizedArray[i]->animal;

        correctSizeArray[i]->color = malloc(sizeof(char) * strlen(colorString));
        strcpy(correctSizeArray[i]->color, colorString);

        correctSizeArray[i]->number = overSizedArray[i]->number;

        correctSizeArray[i]->animal= malloc(sizeof(char) * strlen(animalString));
        strcpy(correctSizeArray[i]->animal, animalString);
    }

    return;
}

