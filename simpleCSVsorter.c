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
char **getArrayOfTokens(char * stringBuffer, const char *delimiter);
int getLine(char line[], int maxLength);


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    // create array that holds 10 movieRecord pointers (10 pointers that each point to a movieRecord)
    struct MovieRecord **arrayOfMovieRecords = malloc(sizeof(struct MovieRecord *) * MAX_NUM_RECORDS);

    if (arrayOfMovieRecords == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrayOfMovieRecords");
        return -1;
    }

    /*
    struct MovieRecord *pMovieA = malloc(sizeof(struct MovieRecord *));
    struct MovieRecord movieA = { "red", 10, "turtle" };
    pMovieA = &movieA;
    arrayOfMovieRecords[0] = pMovieA;

    struct MovieRecord movieB = { "green", 90, "bear" };
    arrayOfMovieRecords[1] = &movieB;

    struct MovieRecord *pMovieC = malloc(sizeof(struct MovieRecord *));
    pMovieC->color = "red";
    pMovieC->number = 777;
    pMovieC->animal= "BULL";
    arrayOfMovieRecords[2] = pMovieC;

    struct MovieRecord *pMovieD = malloc(sizeof(struct MovieRecord *));
    struct MovieRecord movieD = { "blue", 5, "cow" };
    pMovieD = &movieD;
    arrayOfMovieRecords[3] = pMovieD;

    for (int j = 0; j < 5; j++) 
    {
        struct MovieRecord *pTempMovieRecord = malloc(sizeof(struct MovieRecord));
        pTempMovieRecord->color = "red";
        pTempMovieRecord->number= j;
        pTempMovieRecord->animal = "bird";
        arrayOfMovieRecords[j] = pTempMovieRecord;
    }

    for (int i = 0; i < 4; i++) 
    {
        struct MovieRecord *movie = arrayOfMovieRecords[i];
        printf("arrayOfMovieRecords[%d]\tcolor: %s\tnumber: %d\tanimal: %s\t\n", i, movie->color, movie->number, movie->animal); 
        // NULL out the example MovieRecord pointers
        arrayOfMovieRecords[i] = NULL;
    }
    */
 
    // get input from csv
    int numberOfMovieRecords = 0;
    char line[MAX_LINE_LENGTH];
    char **arrayOfTokens = malloc(sizeof(char *) * MAX_NUM_COLUMNS);

    if (arrayOfTokens == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrayOfTokens");
        return -1;
    }

    for (int i = 0; i < MAX_NUM_RECORDS; i++)
    {
        while (getLine(line, MAX_LINE_LENGTH) != EOF)
        {
            //printf("you typed \"%s\"\n", line);
            arrayOfTokens = getArrayOfTokens(line, DELIMITER);
            //printf("arrayOfTokens:\tcolor:%s\tnumber:%s\tanimal:%s\n", arrayOfTokens[0], arrayOfTokens[1], arrayOfTokens[2]);

            struct MovieRecord *pTempMovieRecord = malloc(sizeof(struct MovieRecord));
            pTempMovieRecord->color = arrayOfTokens[0];
            pTempMovieRecord->number= atoi(arrayOfTokens[1]);
            pTempMovieRecord->animal = arrayOfTokens[2];
            arrayOfMovieRecords[i] = pTempMovieRecord;

            //printf("%s,%d,%s\n", arrayOfMovieRecords[i]->color, arrayOfMovieRecords[i]->number, arrayOfMovieRecords[i]->animal);
            numberOfMovieRecords++;
        }

    }

    for (int i = 0; i < numberOfMovieRecords; i++)
    {
        printf("%s,%d,%s\n", arrayOfMovieRecords[i]->color, arrayOfMovieRecords[i]->number, arrayOfMovieRecords[i]->animal);
    }
    //printMovieRecords(arrayOfMovieRecords, numberOfMovieRecords);

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

char **getArrayOfTokens(char *stringBuffer, const char *delimiter)
{
    // initilize array to hold each token
    char **arrayOfTokens = (char **)malloc(sizeof(char *)*30); 
    // declare char[] to hold each token string as it is processed and assign first string returned from strtok
    char *stringToken = strtok(stringBuffer, delimiter); 

    int i = 0;

    while (stringToken != NULL)
    {
        arrayOfTokens[i] = (char *)malloc(sizeof(strlen(stringToken)+1)*sizeof(char));
        strcpy(arrayOfTokens[i], stringToken);
        stringToken = strtok(NULL, delimiter);
        i++;
    }

    return arrayOfTokens;
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
    char aChar;
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
