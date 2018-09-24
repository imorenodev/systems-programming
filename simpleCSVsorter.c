#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "simpleCSVsorter.h"


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);

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
    //char **arrayOfTokens = malloc(sizeof(char *) * MAX_NUM_COLUMNS);
    char *arrayOfTokens[MAX_NUM_COLUMNS];
    char **arrayOfColumnNames = malloc(sizeof(char *) * MAX_NUM_COLUMNS);

    /*
    if (arrayOfTokens == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrayOfTokens");
        return -1;
    }
    */

    /**** process stdin line by line. ****/

    // first line in csv, this is the header row containing the column names 
    // should not be inserted into the array of MovieRecords
    int count;
    if (getLine(line, MAX_LINE_LENGTH) != EOF)
    {
        getArrayOfTokens(arrayOfTokens, line, DELIMITER);
        
        // fill array of ColumnNames with imprecise number of elements
        for (int j = 0; arrayOfTokens[j] != NULL; j++)
        {
            printf("string: %s\n", arrayOfTokens[j]);
            //printf("strlen(arrayOfTokens[j]): %d\n", (int)strlen(arrayOfTokens[j]));
            //printf("sizeof(arrayOfTokens[j]): %d\n", (int)sizeof(arrayOfTokens[j]));
            arrayOfColumnNames[j] = malloc(sizeof(char) * strlen(arrayOfTokens[j]));
            strcpy(arrayOfColumnNames[j], arrayOfTokens[j]);
            //printf("arrayOfTokens[j]:%s\tarrayOfColumnNames[j]:%s\n", arrayOfTokens[j], arrayOfColumnNames[j]);
            count++;
        }
    }
    // resize Array of ColumnNames with exact number of elements
    arrayOfColumnNames = realloc(arrayOfColumnNames, (count*sizeof(char)));

    /** tokenize the line. 
     * save tokens in each struct MovieRecord's corresponding members.
     **/
    count = 0;
    while (getLine(line, MAX_LINE_LENGTH) != EOF)
    {
        getArrayOfTokens(arrayOfTokens, line, DELIMITER);

        // grab temp char * so we can malloc correct size for MovieRecord member
        char *color =           arrayOfTokens[0];
        char *director_name =   arrayOfTokens[1];
        char *actor_2_name =    arrayOfTokens[6];
        char *genres =          arrayOfTokens[9];
        char *actor_1_name =    arrayOfTokens[10];
        char *movie_title =     arrayOfTokens[11];
        char *actor_3_name =    arrayOfTokens[14];
        char *plot_keywords =   arrayOfTokens[16];
        char *movie_imdb_link = arrayOfTokens[17];
        char *language =        arrayOfTokens[19];
        char *country =         arrayOfTokens[20];
        char *content_rating =  arrayOfTokens[21];

        // initialize malloc as necessary for each MovieRecord member
        arrayOfMovies[count]->color =                       malloc(sizeof(char) * strlen(color));
        strcpy(arrayOfMovies[count]->color, color);

        arrayOfMovies[count]->director_name =               malloc(sizeof(char) * strlen(director_name));
        strcpy(arrayOfMovies[count]->director_name, director_name);

        arrayOfMovies[count]->num_critic_for_reviews =      atoi(arrayOfTokens[2]);
        arrayOfMovies[count]->duration =                    atoi(arrayOfTokens[3]);
        arrayOfMovies[count]->director_facebook_likes =     atoi(arrayOfTokens[4]);
        arrayOfMovies[count]->actor_3_facebook_likes =      atoi(arrayOfTokens[5]);

        arrayOfMovies[count]->actor_2_name =                malloc(sizeof(char) * strlen(actor_2_name));
        strcpy(arrayOfMovies[count]->actor_2_name, actor_2_name);

        arrayOfMovies[count]->actor_1_facebook_likes =      atoi(arrayOfTokens[7]);
        arrayOfMovies[count]->gross =                       atoi(arrayOfTokens[8]);

        arrayOfMovies[count]->genres =                      malloc(sizeof(char) * strlen(genres));
        strcpy(arrayOfMovies[count]->genres, genres);

        arrayOfMovies[count]->actor_1_name =                malloc(sizeof(char) * strlen(actor_1_name));
        strcpy(arrayOfMovies[count]->actor_1_name, actor_1_name);

        arrayOfMovies[count]->movie_title =                 malloc(sizeof(char) * strlen(movie_title));
        strcpy(arrayOfMovies[count]->movie_title, movie_title);

        arrayOfMovies[count]->num_voted_users =             atoi(arrayOfTokens[12]);
        arrayOfMovies[count]->cast_total_facebook_likes =   atoi(arrayOfTokens[13]);

        arrayOfMovies[count]->actor_3_name =                malloc(sizeof(char) * strlen(actor_3_name));
        strcpy(arrayOfMovies[count]->actor_3_name, actor_3_name);

        arrayOfMovies[count]->facenumber_in_poster =        atoi(arrayOfTokens[15]);

        arrayOfMovies[count]->plot_keywords =               malloc(sizeof(char) * strlen(plot_keywords));
        strcpy(arrayOfMovies[count]->plot_keywords, plot_keywords);

        arrayOfMovies[count]->movie_imdb_link =             malloc(sizeof(char) * strlen(movie_imdb_link));
        strcpy(arrayOfMovies[count]->movie_imdb_link, movie_imdb_link);

        arrayOfMovies[count]->num_user_for_reviews =        atoi(arrayOfTokens[18]);

        arrayOfMovies[count]->language =                    malloc(sizeof(char) * strlen(language));
        strcpy(arrayOfMovies[count]->language, language);

        arrayOfMovies[count]->country =                     malloc(sizeof(char) * strlen(country));
        strcpy(arrayOfMovies[count]->country, country);

        arrayOfMovies[count]->content_rating =              malloc(sizeof(char) * strlen(content_rating));
        strcpy(arrayOfMovies[count]->content_rating, content_rating);

        arrayOfMovies[count]->budget =                      atoi(arrayOfTokens[22]);
        arrayOfMovies[count]->title_year =                  atoi(arrayOfTokens[23]);
        arrayOfMovies[count]->actor_2_facebook_likes =      atoi(arrayOfTokens[24]);
        arrayOfMovies[count]->imdb_score  =                 atof(arrayOfTokens[25]);
        arrayOfMovies[count]->aspect_ratio =                atof(arrayOfTokens[26]);
        arrayOfMovies[count]->movie_facebook_likes =        atoi(arrayOfTokens[27]);

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

    printf("Orignial Array\n");
    printMovieRecords(count, arrayOfColumnNames, unSortedArrayOfMovies);
    //printf("\nSorted Array\n");
    //printMovieRecords(count, arrayOfColumnNames, sortedArrayOfMovies);

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
        char *token2 = malloc((strlen(token)+1)*sizeof(char));
        if (0 == *token)
        {
            token = empty;
        }

        arrayOfTokens[i] = (char *)malloc(sizeof(strlen(token)+1)*sizeof(char));
        strncpy(arrayOfTokens[i], token, strlen(token)+1);
        
        printf("arrayOfTokens[i]: %s\n", arrayOfTokens[i]);
        i++;
    }
    //printf("arrayOfTokens[2]: %s\n", arrayOfTokens[2]);

    return;
}

void printMovieRecords(int count, char **arrayOfColumnNames, struct MovieRecord **arrayOfMovieRecords)
{
    struct MovieRecord **tempA = arrayOfMovieRecords;

    // print row of ColumnNames first
    int j = 0;
    while (arrayOfColumnNames[j+2] != NULL)
    {
        printf("%s,", arrayOfColumnNames[j]);
        j++;
    }
    // last columnName should not be printed with trailing comma ',' and needs a newline '\n'
    printf("%s\n", arrayOfColumnNames[j]);

    for (int i = 0; i < count; i++)
    {
        printf("%s,%s,%d,%d,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,%.2f,%.2f,%d\n",
                tempA[i]->color, tempA[i]->director_name, tempA[i]->num_critic_for_reviews, tempA[i]->duration,
                tempA[i]->director_facebook_likes, tempA[i]->actor_3_facebook_likes, tempA[i]->actor_2_name,
                tempA[i]->actor_1_facebook_likes, tempA[i]->gross, tempA[i]->genres, tempA[i]->actor_1_name,
                tempA[i]->movie_title, tempA[i]->num_voted_users, tempA[i]->cast_total_facebook_likes, tempA[i]->actor_3_name,
                tempA[i]->facenumber_in_poster, tempA[i]->plot_keywords, tempA[i]->movie_imdb_link, tempA[i]->num_user_for_reviews,
                tempA[i]->language, tempA[i]->country, tempA[i]->content_rating, tempA[i]->budget, tempA[i]->title_year,
                tempA[i]->actor_2_facebook_likes, tempA[i]->imdb_score, tempA[i]->aspect_ratio, tempA[i]->movie_facebook_likes);
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

void copyArrayOfMovies(int count, struct MovieRecord **sourceArray, struct MovieRecord **outputArray)
{
    for (int i = 0; i < count; i++)
    {
        // grab temp char * so we can malloc correct size for MovieRecord member
        char *color =           sourceArray[i]->color;
        char *director_name =   sourceArray[i]->director_name;
        char *actor_2_name =    sourceArray[i]->actor_2_name;
        char *genres =          sourceArray[i]->genres;
        char *actor_1_name =    sourceArray[i]->actor_1_name;
        char *movie_title =     sourceArray[i]->movie_title;
        char *actor_3_name =    sourceArray[i]->actor_3_name;
        char *plot_keywords =   sourceArray[i]->plot_keywords;
        char *movie_imdb_link = sourceArray[i]->movie_imdb_link;
        char *language =        sourceArray[i]->language;
        char *country =         sourceArray[i]->country;
        char *content_rating =  sourceArray[i]->content_rating;

        // initialize malloc as necessary for each MovieRecord member
        outputArray[i]->color =                         malloc(sizeof(char) * strlen(color));
        strcpy(outputArray[i]->color, color);

        outputArray[i]->director_name =                 malloc(sizeof(char) * strlen(director_name));
        strcpy(outputArray[i]->director_name, director_name);

        outputArray[i]->num_critic_for_reviews =        sourceArray[i]->num_critic_for_reviews;
        outputArray[i]->duration =                      sourceArray[i]->duration;
        outputArray[i]->director_facebook_likes =       sourceArray[i]->director_facebook_likes;
        outputArray[i]->actor_3_facebook_likes =        sourceArray[i]->actor_3_facebook_likes;

        outputArray[i]->actor_2_name =                  malloc(sizeof(char) * strlen(actor_2_name));
        strcpy(outputArray[i]->actor_2_name, actor_2_name);

        outputArray[i]->actor_1_facebook_likes =        sourceArray[i]->actor_1_facebook_likes;
        outputArray[i]->gross =                         sourceArray[i]->gross;

        outputArray[i]->genres =                        malloc(sizeof(char) * strlen(genres));
        strcpy(outputArray[i]->genres, genres);

        outputArray[i]->actor_1_name =                  malloc(sizeof(char) * strlen(actor_1_name));
        strcpy(outputArray[i]->actor_1_name, actor_1_name);

        outputArray[i]->movie_title =                   malloc(sizeof(char) * strlen(movie_title));
        strcpy(outputArray[i]->movie_title, movie_title);

        outputArray[i]->num_voted_users =               sourceArray[i]->num_voted_users;
        outputArray[i]->cast_total_facebook_likes =     sourceArray[i]->cast_total_facebook_likes;

        outputArray[i]->actor_3_name =                  malloc(sizeof(char) * strlen(actor_3_name));
        strcpy(outputArray[i]->actor_3_name, actor_3_name);

        outputArray[i]->facenumber_in_poster =          sourceArray[i]->facenumber_in_poster;

        outputArray[i]->plot_keywords =                 malloc(sizeof(char) * strlen(plot_keywords));
        strcpy(outputArray[i]->plot_keywords, plot_keywords);

        outputArray[i]->movie_imdb_link =               malloc(sizeof(char) * strlen(movie_imdb_link));
        strcpy(outputArray[i]->movie_imdb_link, movie_imdb_link);

        outputArray[i]->num_user_for_reviews =          sourceArray[i]->num_user_for_reviews;

        outputArray[i]->language =                      malloc(sizeof(char) * strlen(language));
        strcpy(outputArray[i]->language, language);

        outputArray[i]->country =                       malloc(sizeof(char) * strlen(country));
        strcpy(outputArray[i]->country, country);

        outputArray[i]->content_rating =                malloc(sizeof(char) * strlen(content_rating));
        strcpy(outputArray[i]->content_rating, content_rating);

        outputArray[i]->budget =                        sourceArray[i]->budget;
        outputArray[i]->title_year =                    sourceArray[i]->title_year;
        outputArray[i]->actor_2_facebook_likes =        sourceArray[i]->actor_2_facebook_likes;
        outputArray[i]->imdb_score  =                   sourceArray[i]->imdb_score;
        outputArray[i]->aspect_ratio =                  sourceArray[i]->aspect_ratio;
        outputArray[i]->movie_facebook_likes =          sourceArray[i]->movie_facebook_likes;

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
        if (strcmp(columnName, "color") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->color, tempArray2[index2]->color) < 0)))
                // tempArray1 exists and is smaller
                // swap pointers
                outputArray[indexOutput++] = tempArray1[index1++];
                // tempArray1 doesn't exist OR is larger than tempArray2[index2]
                // swap pointers
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "director_name") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->director_name, tempArray2[index2]->director_name) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "num_critic_for_reviews") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->num_critic_for_reviews < tempArray2[index2]->num_critic_for_reviews)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "duration") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->duration < tempArray2[index2]->duration)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "director_facebook_likes") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->director_facebook_likes < tempArray2[index2]->director_facebook_likes)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "actor_3_facebook_likes") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->actor_3_facebook_likes < tempArray2[index2]->actor_3_facebook_likes)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "actor_2_name") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->actor_2_name, tempArray2[index2]->actor_2_name) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "actor_1_facebook_likes") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->actor_1_facebook_likes < tempArray2[index2]->actor_1_facebook_likes)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "gross") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->gross < tempArray2[index2]->gross)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "genres") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->genres, tempArray2[index2]->genres) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "actor_1_name") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->actor_1_name, tempArray2[index2]->actor_1_name) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "movie_title") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->movie_title, tempArray2[index2]->movie_title) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "num_voted_users") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->num_voted_users < tempArray2[index2]->num_voted_users)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "cast_total_facebook_likes") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->cast_total_facebook_likes < tempArray2[index2]->cast_total_facebook_likes)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "actor_3_name") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->actor_3_name, tempArray2[index2]->actor_3_name) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "facenumber_in_poster") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->facenumber_in_poster < tempArray2[index2]->facenumber_in_poster)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "plot_keywords") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->plot_keywords, tempArray2[index2]->plot_keywords) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "movie_imdb_link") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->movie_imdb_link, tempArray2[index2]->movie_imdb_link) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "num_user_for_reviews") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->num_user_for_reviews < tempArray2[index2]->num_user_for_reviews)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "language") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->language, tempArray2[index2]->language) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "country") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->country, tempArray2[index2]->country) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "content_rating") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (strcmp(tempArray1[index1]->content_rating, tempArray2[index2]->content_rating) < 0)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "budget") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->budget < tempArray2[index2]->budget)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        }  else if (strcmp(columnName, "title_year") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->title_year < tempArray2[index2]->title_year)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "actor_2_facebook_likes") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->actor_2_facebook_likes < tempArray2[index2]->actor_2_facebook_likes)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "imdb_score") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->imdb_score < tempArray2[index2]->imdb_score)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "aspect_ratio") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->aspect_ratio < tempArray2[index2]->aspect_ratio)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else if (strcmp(columnName, "movie_facebook_likes") == 0) {
            if (index2 >= count2 || ((index1 < count1) && (tempArray1[index1]->movie_facebook_likes < tempArray2[index2]->movie_facebook_likes)))
                outputArray[indexOutput++] = tempArray1[index1++];
            else
                outputArray[indexOutput++] = tempArray2[index2++];
        } else {
          fprintf(stderr, "Fatal Error:\t Invalid ColumnName.");
          exit(0);
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
    } else if ((strcmp(argv[2], "color") != 0) && (strcmp(argv[2], "director_name") != 0) && (strcmp(argv[2], "num_critic_for_reviews") != 0) &&
              (strcmp(argv[2], "duration") != 0) && (strcmp(argv[2], "director_facebook_likes") != 0) && (strcmp(argv[2], "actor_3_facebook_likes") != 0) &&
              (strcmp(argv[2], "actor_2_name") != 0) && (strcmp(argv[2], "actor_1_facebook_likes") != 0) && (strcmp(argv[2], "gross") != 0) &&
              (strcmp(argv[2], "genres") != 0) && (strcmp(argv[2], "actor_1_name") != 0) && (strcmp(argv[2], "movie_title") != 0) &&
              (strcmp(argv[2], "num_voted_users") != 0) && (strcmp(argv[2], "cast_total_facebook_likes") != 0) && (strcmp(argv[2], "actor_3_name") != 0) &&
              (strcmp(argv[2], "facenumber_in_poster") != 0) && (strcmp(argv[2], "plot_keywords") != 0) && (strcmp(argv[2], "movie_imdb_link") != 0) &&
              (strcmp(argv[2], "num_user_for_reviews") != 0) && (strcmp(argv[2], "language") != 0) && (strcmp(argv[2], "country") != 0) &&
              (strcmp(argv[2], "content_rating") != 0) && (strcmp(argv[2], "budget") != 0) && (strcmp(argv[2], "title_year") != 0) &&
              (strcmp(argv[2], "actor_2_facebook_likes") != 0) && (strcmp(argv[2], "imdb_score") != 0) && (strcmp(argv[2], "aspect_ratio") != 0) &&
              (strcmp(argv[2], "movie_facebook_likes") != 0)) {
        fprintf(stderr, "Fatal Error:\t%s is Not a Valid ColumnName.\n", argv[2]);
        return -1;
    }

    return 0;
}

