#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "simpleCSVsorter.h"


// Struct
struct movieRecord {
    char *color;
    int number;
    char *animal;
};

void printArguments(int argCount, char *argArray[]);
void processInput(struct movieRecord **arrayOfPtrsToMovieRecords);
void processOutput(struct movieRecord **arrayOfPtrsToMovieRecords);


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    // create array that holds 5 movieRecord pointers (5 pointers that each point to a movieRecord)
    struct movieRecord **arrayOfPtrsToMovieRecords = (struct movieRecord **)malloc(sizeof(struct movieRecord *)*10);;

    if (arrayOfPtrsToMovieRecords == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrMovieRecords");
        return -1;
    }

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

void processInput(struct movieRecord **arrayOfPtrsToMovieRecords) 
{
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

    //printf("movieA: color=%s number=%d animal=%s\n", arrayOfPtrsToMovieRecords[0]->color, arrayOfPtrsToMovieRecords[0]->number, arrayOfPtrsToMovieRecords[0]->animal);
    
    return;
}

void processOutput(struct movieRecord **arrayOfPtrsToMovieRecords)
{
    printf("movieA: color=%s number=%d animal=%s\n", arrayOfPtrsToMovieRecords[2]->color, arrayOfPtrsToMovieRecords[2]->number, arrayOfPtrsToMovieRecords[2]->animal);

    return;
}
