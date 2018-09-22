#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "simpleCSVsorter.h"


// Struct
struct MovieRecord {
    char *color;
    int number;
    char *animal;
};

void printArguments(int argCount, char *argArray[]);
void printMovieRecords(struct MovieRecord **arrayOfMovieRecords, int lengthOfArrayOfMovieRecords);
void getArrayOfTokens(char **arrayOfTokens, char * line, const char *delimiter);
int getLine(char line[], int maxLength);


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    // create array that holds 10 movieRecord pointers (10 pointers that each point to a movieRecord)
    //struct MovieRecord **arrayOfMovieRecords = malloc(sizeof(struct MovieRecord *) * MAX_NUM_RECORDS);
    struct MovieRecord *arrayOfMovies[10];

    for (int i = 0; i < MAX_NUM_RECORDS+1; i++)
    {
        arrayOfMovies[i] = malloc(sizeof(struct MovieRecord));
    }
    arrayOfMovies[0]->color = malloc(sizeof(char)*sizeof("orange"));
    arrayOfMovies[0]->animal= malloc(sizeof(char)*sizeof("horse"));
    strcpy(arrayOfMovies[0]->color, "orange");
    arrayOfMovies[0]->number = 99;
    strcpy(arrayOfMovies[0]->animal, "horse");
    printf("TESTING color:%s\tnumber:%d\tanimal:%s\n", arrayOfMovies[0]->color, arrayOfMovies[0]->number, arrayOfMovies[0]->animal);

    arrayOfMovies[1]->color = malloc(sizeof(char)*sizeof("orange"));
    arrayOfMovies[1]->animal= malloc(sizeof(char)*sizeof("horse"));
    strcpy(arrayOfMovies[1]->color, "orange");
    arrayOfMovies[1]->number = 99;
    strcpy(arrayOfMovies[1]->animal, "horse");
    printf("TESTING color:%s\tnumber:%d\tanimal:%s\n", arrayOfMovies[1]->color, arrayOfMovies[1]->number, arrayOfMovies[1]->animal);
    
   
    // get input from csv
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
        /***DELETE
        // initilize array to hold each token
        // declare char[] to hold each token string as it is processed and assign first string returned from strtok
        char *stringToken = strtok(line, DELIMITER); 
        int k = 0;

        while (stringToken != NULL)
        {
            arrayOfTokens[k] = (char *)malloc(sizeof(strlen(stringToken)+1)*sizeof(char));
            strcpy(arrayOfTokens[k], stringToken);
            stringToken = strtok(NULL, DELIMITER);
            k++;
        }
        DELETE***/

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
