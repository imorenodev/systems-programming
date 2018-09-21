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
char **getArrayOfTokens(char * stringBuffer, const char *delimiter);


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    // create array that holds 5 movieRecord pointers (5 pointers that each point to a movieRecord)
    struct MovieRecord *arrayOfMovieRecords = malloc(sizeof(struct MovieRecord) * 5);

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

    printf("\n");

    // get input from csv
    //char *buffer = (char*)malloc(sizeof(char)*2000);
    char buffer[4];
    char *bufferString = 0;
    size_t currentLength = 0;
    size_t currentMaxLength = 0;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        size_t bufferLength = strlen(buffer);
        if ((currentLength + bufferLength + 1) > currentMaxLength)
        {
            size_t newLength = ((currentMaxLength*2) + 1);

            if ((bufferLength + 1) > newLength)
            {
                newLength = (bufferLength + 1);
            }

            char *tempBufferString = realloc(bufferString, newLength);

            if (tempBufferString == 0)
            {
                break;
            }
            bufferString = tempBufferString;
            currentMaxLength = newLength;
        }
        strcpy(bufferString + currentLength, buffer);
        currentLength += bufferLength;

    }
    printf("%s [%d]\n", bufferString, (int)strlen(bufferString));

        /** temp comment out
        if (strcmp(buffer,"\n") != 0)
        {
            printf("BUFFER:\t%s", buffer);

            const char *DELIMITER = ",";

            char **arrayOfTokens = getArrayOfTokens(buffer, DELIMITER);

            for (int i = 0; i < 30; i++) 
            {
                printf("TOKEN LENGTH:\t%lu\tTOKEN:%s\n\n", strlen(arrayOfTokens[i]), arrayOfTokens[i]);
            }
        }
        **/

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

char **getArrayOfTokens(char * stringBuffer, const char *delimiter)
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
