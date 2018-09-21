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

    /*
    // get input from csv
    //processInput(arrayOfPtrsToMovieRecords);
    // get input from csv
    char *buffer = (char*)malloc(sizeof(char)*2000);
    int lineNumber = 0;

    while (fgets(buffer, 2000, stdin) != NULL)
    {
        if (strcmp(buffer,"\n") != 0)
        {
            const char *DELIMITER = ",";
            // get first comma-delimited "token" from first line of stdin input
            char *stringToken = malloc(sizeof(char)*20);
            stringToken = strtok(buffer, DELIMITER);

            while(stringToken != NULL)
            {
                // iterate to a movieRecord-pointer in the array and assign it the address to a piece of memory 
                // to hold a future movieRecord-struct
                arrayOfPtrsToMovieRecords[lineNumber] = (struct movieRecord *)malloc(sizeof(struct movieRecord));

                arrayOfPtrsToMovieRecords[lineNumber]->color = stringToken;
                stringToken = strtok(NULL, DELIMITER);
                arrayOfPtrsToMovieRecords[lineNumber]->number= atoi(stringToken);
                stringToken = strtok(NULL, DELIMITER);
                arrayOfPtrsToMovieRecords[lineNumber]->animal= stringToken;
                stringToken = strtok(NULL, DELIMITER);
            }
            //printf("movieA: color=%s number=%d animal=%s\n", arrayOfPtrsToMovieRecords[lineNumber]->color, arrayOfPtrsToMovieRecords[lineNumber]->number, arrayOfPtrsToMovieRecords[lineNumber]->animal);
            lineNumber++;
        }
    }

    printf("movieA: color=%s number=%d animal=%s\n", arrayOfPtrsToMovieRecords[0]->color, arrayOfPtrsToMovieRecords[0]->number, arrayOfPtrsToMovieRecords[0]->animal);
    printf("movieA: color=%s number=%d animal=%s\n", arrayOfPtrsToMovieRecords[1]->color, arrayOfPtrsToMovieRecords[2]->number, arrayOfPtrsToMovieRecords[2]->animal);
 

    //processOutput(arrayOfPtrsToMovieRecords);
    */

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
