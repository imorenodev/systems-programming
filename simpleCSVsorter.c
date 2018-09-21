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
void printMovieRecords(struct MovieRecord *arrayOfMovieRecords, int lengthOfArrayOfMovieRecords);
char **getArrayOfTokens(char * stringBuffer, const char *delimiter);
int getLine(char line[], int maxLength);


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    // create array that holds 10 movieRecord pointers (10 pointers that each point to a movieRecord)
    struct MovieRecord **arrayOfMovieRecords = malloc(sizeof(struct MovieRecord *) * 10);

    if (arrayOfMovieRecords == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrayOfMovieRecords");
        return -1;
    }

    struct MovieRecord movieA = { "red", 10, "turtle" };
    struct MovieRecord movieB = { "green", 90, "bear" };
    struct MovieRecord movieC = { "black", 20, "cat" };
    struct MovieRecord movieD = { "blue", 5, "cow" };

    arrayOfMovieRecords[0] = movieA;
    arrayOfMovieRecords[1] = movieB;
    arrayOfMovieRecords[2] = movieC;
    arrayOfMovieRecords[3] = movieD;

    for (int i = 0; i < 5; i++) 
    {
        struct MovieRecord *movie = malloc(sizeof(struct MovieRecord*));
        movie = &(arrayOfMovieRecords[i]);
        printf("arrayOfMovieRecords[%d]\tcolor: %s\tnumber: %d\tanimal: %s\t\n", i, movie->color, movie->number, movie->animal); 
    }
    */

    printf("\n");

    // get input from csv
    char line[MAX_LINE_LENGTH];
    char **arrayOfTokens = malloc(sizeof(char *)*30);

    for (int i = 0; i < 4; i++)
    {
        while (getLine(line, MAX_LINE_LENGTH) != EOF)
        {
            //printf("you typed \"%s\"\n", line);
            arrayOfTokens = getArrayOfTokens(line, DELIMITER);
            //printf("arrayOfTokens:\tcolor:%s\tnumber:%s\tanimal:%s\n", arrayOfTokens[0], arrayOfTokens[1], arrayOfTokens[2]);
            
            arrayOfMovieRecords[i].color = arrayOfTokens[0];
            arrayOfMovieRecords[i].number = atoi(arrayOfTokens[1]);
            arrayOfMovieRecords[i].animal = arrayOfTokens[2];
        }

    }

    printMovieRecords(arrayOfMovieRecords, 4);

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

void printMovieRecords(struct MovieRecord *arrayOfMovieRecords, int lengthOfArrayOfMovieRecords)
{
   for (int i = 0; i < lengthOfArrayOfMovieRecords; i++)
   {
        printf("%s,%d,%s\n", arrayOfMovieRecords[i].color, arrayOfMovieRecords[i].number, arrayOfMovieRecords[i].animal);
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
        return EOF;

    line[index] = '\0';
    return index;
}
