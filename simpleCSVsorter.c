#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "simpleCSVsorter.h"



int main(int argc, char *argv[])
{
    printArguments(argc, argv);

    if (isValidArguments(argc, argv) != 0) 
    {
        return -1;
    }
    const char *columnName = argv[2];
    
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

    // create new array of pointers to struct MovieRecords to hold accurate number of MovieRecords
    struct MovieRecord *unSortedArrayOfMovies[count];
    initializeArrayOfMovies(count, unSortedArrayOfMovies);
    // copy contents of oversized array of MovieRecords to new array of correct size
    copyArrayOfMovies(count, arrayOfMovies, unSortedArrayOfMovies);

    // create new array of pointers to struct MovieRecords to hold sorted MovieRecords
    struct MovieRecord *sortedArrayOfMovies[count];
    initializeArrayOfMovies(count, sortedArrayOfMovies);

    // sort the records and save sorted output in sortedArrayOfMovies
    mergeSort(count, columnName, arrayOfMovies, sortedArrayOfMovies);

    /**
    printf("Orignial Array\n");
    printMovieRecords(count, unSortedArrayOfMovies);
    **/
    printf("\nSorted Array\n");
    printMovieRecords(count, sortedArrayOfMovies);

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
    char *empty = " ";
    char *token;
    int i = 0;

    while ((token = strsep(&line, delimiter)))
    {
        if (0 == *token)
        {
            token = empty;
        }
        arrayOfTokens[i] = (char *)malloc(sizeof(strlen(token)+1)*sizeof(char));
        strcpy(arrayOfTokens[i], token);
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
    //printf("inside initializeArrayOfMovies... numberOfRecords: %d\t pointer to arrayOfMovies: %p\n", numberOfRecords, arrayOfMovies);
    for (int i = 0; i < numberOfRecords; i++)
    {
        arrayOfMovies[i] = malloc(sizeof(struct MovieRecord));
    }

    return;
}

void copyArrayOfMovies(int count, struct MovieRecord **sourceArray, struct MovieRecord **outputArray)
{
    for (int i = 0; i < count; i++)
    {
        // grab temporary strings from sourceArray so we can count the length for malloc initialization
        char *colorString = sourceArray[i]->color;
        char *animalString = sourceArray[i]->animal;

        outputArray[i]->color = malloc(sizeof(char) * strlen(colorString));
        strcpy(outputArray[i]->color, colorString);

        outputArray[i]->number = sourceArray[i]->number;

        outputArray[i]->animal= malloc(sizeof(char) * strlen(animalString));
        strcpy(outputArray[i]->animal, animalString);
    }

    return;
}

void mergeSort(int count, const char *columnName, struct MovieRecord **sourceArray, struct MovieRecord **outputArray)
{
    struct MovieRecord *tempArray1[(count/2)];
    struct MovieRecord *tempArray2[(count - (count/2))];
    
    if (count < 2) {
        // sourceArray already sorted
        copyArrayOfMovies(count, sourceArray, outputArray);
    } else {
        // initialize tempArray1 to hold first half of MovieRecords
        initializeArrayOfMovies((count/2), tempArray1);

        // initialize tempArray2 to hold last half of MovieRecords
        initializeArrayOfMovies((count - (count/2)), tempArray2);

        // sort first half
        mergeSort((count/2), columnName, sourceArray, tempArray1);

        // sort second half
        mergeSort((count - (count/2)), columnName, (sourceArray + (count/2)), tempArray2);

        merge((count/2), columnName, tempArray1, (count - (count/2)), tempArray2, outputArray);
    }

    return;
}

void merge(int count1, const char *columnName, struct MovieRecord **tempArray1, int count2, struct MovieRecord **tempArray2, struct MovieRecord **outputArray)
{
    int index1 = 0;
    int index2 = 0;
    int indexOutput = 0;
    int compareValue = 0;

    while (index1 < count1 || index2 < count2)
    {
        if (strcmp(columnName, "number") == 0) 
        {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->number < tempArray2[index2]->number)))
            {
                // tempArray1 exists and is smaller
                // swap pointers
                outputArray[indexOutput++] = tempArray1[index1++];
            } else {
                // tempArray1 doesn't exist OR is larger than tempArray2[index2]
                // swap pointers
                outputArray[indexOutput++] = tempArray2[index2++];
            }
        } else if (strcmp(columnName, "color") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->color, tempArray2[index2]->color) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "animal") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->animal, tempArray2[index2]->animal) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        }
    }

    return;
}

int isValidArguments(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Fatal Error:\tInvalid Number of Arguments.\n");
        return -1;
    } else if (strcmp(argv[1], "-c") != 0) {
        fprintf(stderr, "Fatal Error:\tInvalid Sort Flag. Expected \"-c\"\n");
        return -1;
    } else if ((strcmp(argv[2], "animal") != 0) && (strcmp(argv[2], "color") != 0) && (strcmp(argv[2], "number") != 0)) {
        fprintf(stderr, "Fatal Error:\t%s is Not a Valid ColumnName.\n", argv[2]);
        return -1;
    }

    return 0;
}

