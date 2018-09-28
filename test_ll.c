#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie_record.h"

#define DELIMITER           ","

void printMovieRecord(struct MovieRecord_Node *head);
char *readToken(char *lineBuffer, char *tokenBuffer);
enum Type getType(char *columnHeaderIndex);


int main(int argc, char** argv)
{
  char* lineBuffer = NULL;
  size_t lineLength = 0;
  size_t read = 0;
  int isHeaderRow = 0;
  char* token = malloc(sizeof(char*)*100);

  /*****************************************
  ** INITIALIZE COLUMN HEADER LL POINTERS **
  *****************************************/
  // pointer to keep track of first ColumnHeader_Node in the LL
  struct ColumnHeader_Node* pHead_ColumnHeader_Node = malloc(sizeof(struct ColumnHeader_Node));
  pHead_ColumnHeader_Node->value= NULL;
  pHead_ColumnHeader_Node->next = NULL;
  // pointer to keep track of current ColumnHeader_Node in the LL
  struct ColumnHeader_Node* current_ColumnHeader_Node = malloc(sizeof(struct ColumnHeader_Node));
  current_ColumnHeader_Node->value= NULL;
  current_ColumnHeader_Node->next = NULL;

  // assign the memory address to the first ColumnHeader node to the pHead_ColumnHeader_Node's ->next
  pHead_ColumnHeader_Node->next = malloc(sizeof(struct ColumnHeader_Node*));
  pHead_ColumnHeader_Node->next = current_ColumnHeader_Node;


  /****************************************
  ** INITIALIZE MOVIE RECORD LL POINTERS **
  ****************************************/
  // pointer to keep track of first MovieRecord_Node in the LL
  struct MovieRecord_Node* pHead_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node));
  pHead_MovieRecord_Node->pHead_MovieDataColumn_Node = NULL;
  pHead_MovieRecord_Node->next = NULL;

  // pointer to keep track of current MovieRecord_Node in the LL
  struct MovieRecord_Node* current_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node));
  current_MovieRecord_Node->pHead_MovieDataColumn_Node = NULL;
  current_MovieRecord_Node->next = NULL;

  // assign the memory address to the first ColumnHeader node to the pHead_ColumnHeader_Node's ->next
  pHead_MovieRecord_Node->next = malloc(sizeof(struct MovieRecord_Node*));
  pHead_MovieRecord_Node->next = current_MovieRecord_Node;

  struct MovieDataColumn_Node* current_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
  current_MovieDataColumn_Node->dataColumn = NULL;
  current_MovieDataColumn_Node->next = NULL;

  // printf("pHead_ColumnHeader_Node: %p\n", pHead_ColumnHeader_Node);
  // printf("pHead_ColumnHeader_Node->next: %p\n", pHead_ColumnHeader_Node->next);
  // printf("current_ColumnHeader_Node: %p\n", current_ColumnHeader_Node);
  //
  // printf("pHead_MovieRecord_Node: %p\n", pHead_MovieRecord_Node);
  // printf("pHead_MovieRecord_Node->next: %p\n", pHead_MovieRecord_Node->next);
  // printf("current_MovieRecord_Node: %p\n", current_MovieRecord_Node);

  // get first line of input (outside of the while loop) to handle the header column
  read = getline(&lineBuffer, &lineLength, stdin);
  while (read != -1)
  {
    if (isHeaderRow == 0) // get column headers
    {
      while (*lineBuffer)
      {
        lineBuffer = readToken(lineBuffer, token);

        //for the MovieRecordColumnHeader that is at the location currently pointed to by current_ColumnHeader_Node
        //set it's columnHeader name
        current_ColumnHeader_Node->value = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(current_ColumnHeader_Node->value, token);
        current_ColumnHeader_Node->next = NULL;
        //printf("token: %s\tcurrent_ColumnHeader_Node->value: %s\n", token, current_ColumnHeader_Node->value);

        // if there are still tokens left to process, then create a new ColumnHeader_Node and append to LL
        if (lineBuffer != NULL)
        {
          // set it's next node to point to the address of the new ColumnHeader_Node pointed to by tempColumnHeader_Node
          current_ColumnHeader_Node->next = malloc(sizeof(struct ColumnHeader_Node));
          current_ColumnHeader_Node = current_ColumnHeader_Node->next;
        }
      }

      // DONE WITH HEADER COLUMNS
      // Read next line to prime for the
      // MovieRecord parsing on the next loop

      isHeaderRow = -1;
      lineBuffer = NULL;
      read = getline(&lineBuffer, &lineLength, stdin);
    } else { // get MovieRecords
      printf("**HEAD/FIRST current_MovieDataColumn_Node: %p\n", current_MovieDataColumn_Node);
      //set the record for the MovieRecord that is at the location currently pointed to by current_MovieRecord_Node
      current_MovieRecord_Node->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
      current_MovieRecord_Node->pHead_MovieDataColumn_Node->dataColumn = NULL;
      current_MovieRecord_Node->pHead_MovieDataColumn_Node->next = malloc(sizeof(struct MovieDataColumn_Node*));
      current_MovieRecord_Node->pHead_MovieDataColumn_Node->next = current_MovieDataColumn_Node;

      // point current_ColumnHeader_Node back to HEAD (start) of columnHeader LL
      // so we can loop through column header names and assign for each new MovieRecord MovieDataColumn
      current_ColumnHeader_Node = pHead_ColumnHeader_Node->next;

      while (*lineBuffer)
      {
        //printf("**NEXT current_MovieDataColumn_Node: %p\n", current_MovieDataColumn_Node);
        lineBuffer = readToken(lineBuffer, token);

        char *columnName = malloc(sizeof(char) * (strlen(current_ColumnHeader_Node->value) + 1));
        strcpy(columnName, current_ColumnHeader_Node->value);
        if (current_ColumnHeader_Node->next != NULL) {
          current_ColumnHeader_Node = current_ColumnHeader_Node->next;
        }

        current_MovieDataColumn_Node->dataColumn = malloc(sizeof(struct MovieDataColumn));
        current_MovieDataColumn_Node->dataColumn->columnName = malloc(sizeof(char) * (strlen(columnName) + 1));
        strcpy(current_MovieDataColumn_Node->dataColumn->columnName, columnName);

        //DO I NEED THIS? current_MovieDataColumn_Node->dataColumn->dataType = malloc(sizeof(enum Type));
        current_MovieDataColumn_Node->dataColumn->dataType = getType(columnName);

        if (current_MovieDataColumn_Node->dataColumn->dataType == STRING) {
          current_MovieDataColumn_Node->dataColumn->s = malloc(sizeof(char) * (strlen(token) + 1));
          strcpy(current_MovieDataColumn_Node->dataColumn->s, token);
        } else if (current_MovieDataColumn_Node->dataColumn->dataType == FLOATS) {
          current_MovieDataColumn_Node->dataColumn->f = atof(token);
        } else if (current_MovieDataColumn_Node->dataColumn->dataType == INTS) {
          current_MovieDataColumn_Node->dataColumn->i = atoi(token);
        } else {
          fprintf(stderr, "Fatal Error: Invalid MovieData DataType");
          exit(0);
        }

        current_MovieDataColumn_Node->next = NULL;

        // if there are still tokens left to process, then create a new MovieDataColumn_Node and append to LL
        if (lineBuffer != NULL)
        {
          // for the MovieDataColumn that is at the location currently pointed to by current_MovieDataColumn_Node
          // set it's next node to point to the address of the new MovieDataColumn_Node pointed to by tempMovieDataColumn_Node
          current_MovieDataColumn_Node->next = malloc(sizeof(struct MovieDataColumn_Node));
          //printf("malloced\tcurrent_MovieDataColumn_Node->next: %p\n", current_MovieDataColumn_Node->next);
          // now assign the pointer variable named current_MovieDataColumn_Node the new address stored in tempMovieDataColumn_Node
          current_MovieDataColumn_Node = current_MovieDataColumn_Node->next;
          current_MovieDataColumn_Node->dataColumn = NULL;
          current_MovieDataColumn_Node->next = NULL;
          //printf("LOOP\tcurrent_MovieDataColumn_Node: %p\n", current_MovieDataColumn_Node);
        }
      }

      // Finished with a MovieRecord, prime getLine for next iteration
      // and create and point to the next (new) MovieRecord Node

      read = getline(&lineBuffer, &lineLength, stdin);

      current_MovieRecord_Node->next = NULL;
      current_MovieDataColumn_Node = NULL;

      printf("current_MovieRecord_Node %p\n", current_MovieRecord_Node);
      if (read != -1)
      {
        current_MovieRecord_Node->next = malloc(sizeof(struct MovieRecord_Node));
        current_MovieRecord_Node = current_MovieRecord_Node->next;
        current_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
      }
    }
  }


  // printf("AFTER FILLING\n");
  // printf("pHead_ColumnHeader_Node: %p\n", pHead_ColumnHeader_Node);
  // printf("pHead_ColumnHeader_Node->next: %p\n", pHead_ColumnHeader_Node->next);
  // printf("current_ColumnHeader_Node: %p\n", current_ColumnHeader_Node);
  //
  // printf("pHead_MovieRecord_Node: %p\n", pHead_MovieRecord_Node);
  // printf("pHead_MovieRecord_Node->next: %p\n", pHead_MovieRecord_Node->next);
  // printf("current_MovieRecord_Node: %p\n", current_MovieRecord_Node);

  // PRINT COLUMN HEADERS

  current_ColumnHeader_Node = pHead_ColumnHeader_Node->next;

  while (current_ColumnHeader_Node->value != NULL)
  {
    printf("%s\n", current_ColumnHeader_Node->value);
    if (current_ColumnHeader_Node->next != NULL)
    {
      current_ColumnHeader_Node = current_ColumnHeader_Node->next;
    } else {
      break;
    }
  }

  // PRINT MOVIE RECORDS

  // printf("\nBEFORE PRINT MOVIE RECORDS\n");
  // printf("current_MovieRecord_Node: %p\n", current_MovieRecord_Node);
      printf("\n\ncurrent_MovieRecord_Node %p\n", current_MovieRecord_Node);
  current_MovieRecord_Node = pHead_MovieRecord_Node->next;
      printf("current_MovieRecord_Node %p\n", current_MovieRecord_Node);
  // printf("current_MovieRecord_Node: %p\n", current_MovieRecord_Node);
  // printf("current_MovieRecord_Node->pHead_MovieDataColumn_Node: %p\n", current_MovieRecord_Node->pHead_MovieDataColumn_Node);
  // printf("current_MovieRecord_Node->pHead_MovieDataColumn_Node->next: %p\n", current_MovieRecord_Node->pHead_MovieDataColumn_Node->next);
  // printf("current_MovieRecord_Node->pHead_MovieDataColumn_Node->dataColumn: %p\n", current_MovieRecord_Node->pHead_MovieDataColumn_Node->dataColumn);
  // printf("DESPERATE TEST: %p\n", pHead_MovieRecord_Node->next->pHead_MovieDataColumn_Node->next->dataColumn);

  while (current_MovieRecord_Node != NULL && current_MovieRecord_Node->pHead_MovieDataColumn_Node != NULL)
  {
    current_MovieDataColumn_Node = current_MovieRecord_Node->pHead_MovieDataColumn_Node->next;

    printf("MADE IT!\n");
    while (current_MovieDataColumn_Node != NULL)
    {
      if (current_MovieDataColumn_Node->dataColumn != NULL)
      {
        if (current_MovieDataColumn_Node->dataColumn->dataType == STRING)
          printf("columnName: %s, data: %s\n", current_MovieDataColumn_Node->dataColumn->columnName, current_MovieDataColumn_Node->dataColumn->s);
        else if (current_MovieDataColumn_Node->dataColumn->dataType == INTS)
          printf("columnName: %s, data: %d\n", current_MovieDataColumn_Node->dataColumn->columnName, current_MovieDataColumn_Node->dataColumn->i);
        else if (current_MovieDataColumn_Node->dataColumn->dataType == FLOATS)
          printf("columnName: %s, data: %lf\n", current_MovieDataColumn_Node->dataColumn->columnName, current_MovieDataColumn_Node->dataColumn->f);
        else {
          fprintf(stderr, "Fatal Error:\t Invalid DataType.");
          exit(0);
        }
      }

      if (current_MovieDataColumn_Node->next != NULL)
      {
        current_MovieDataColumn_Node = current_MovieDataColumn_Node->next;
      } else {
        break;
      }
    } // end while

    if (current_MovieRecord_Node->next != NULL)
    {
      current_MovieRecord_Node = current_MovieRecord_Node->next;
    } else {
      break;
    }
  }

  return 0;
}

enum Type getType(char *columnName)
{
  if (strcmp(columnName, "color") == 0) {
    return STRING;
  } else if (strcmp(columnName, "director_name") == 0) {
    return STRING;
  } else if (strcmp(columnName, "num_critic_for_reviews") == 0) {
    return INTS;
  } else if (strcmp(columnName, "duration") == 0) {
    return INTS;
  } else if (strcmp(columnName, "director_facebook_likes") == 0) {
    return INTS;
  } else if (strcmp(columnName, "actor_3_facebook_likes") == 0) {
    return INTS;
  } else if (strcmp(columnName, "actor_2_name") == 0) {
    return STRING;
  } else if (strcmp(columnName, "actor_1_facebook_likes") == 0) {
    return INTS;
  } else if (strcmp(columnName, "gross") == 0) {
    return INTS;
  } else if (strcmp(columnName, "genres") == 0) {
    return STRING;
  } else if (strcmp(columnName, "actor_1_name") == 0) {
    return STRING;
  } else if (strcmp(columnName, "movie_title") == 0) {
    return STRING;
  } else if (strcmp(columnName, "num_voted_users") == 0) {
    return INTS;
  } else if (strcmp(columnName, "cast_total_facebook_likes") == 0) {
    return INTS;
  } else if (strcmp(columnName, "actor_3_name") == 0) {
    return STRING;
  } else if (strcmp(columnName, "facenumber_in_poster") == 0) {
    return INTS;
  } else if (strcmp(columnName, "plot_keywords") == 0) {
    return STRING;
  } else if (strcmp(columnName, "movie_imdb_link") == 0) {
    return STRING;
  } else if (strcmp(columnName, "num_user_for_reviews") == 0) {
    return INTS;
  } else if (strcmp(columnName, "language") == 0) {
    return STRING;
  } else if (strcmp(columnName, "country") == 0) {
    return STRING;
  } else if (strcmp(columnName, "content_rating") == 0) {
    return STRING;
  } else if (strcmp(columnName, "budget") == 0) {
    return INTS;
  }  else if (strcmp(columnName, "title_year") == 0) {
    return INTS;
  } else if (strcmp(columnName, "actor_2_facebook_likes") == 0) {
    return INTS;
  } else if (strcmp(columnName, "imdb_score") == 0) {
    return FLOATS;
  } else if (strcmp(columnName, "aspect_ratio") == 0) {
    return FLOATS;
  } else if (strcmp(columnName, "movie_facebook_likes") == 0) {
    return INTS;
  } else {
    fprintf(stderr, "Fatal Error:\t Invalid ColumnName.");
    exit(0);
  }
}

char *readToken(char *lineBuffer, char *tokenBuffer)
{
    int inString = -1;   // track whether we are in a string
    char *charPtr = lineBuffer;

    while (*charPtr)
    {
        //printf("charPtr: %s\n", charPtr);
        if (inString == 0)
        {
            if (*charPtr == '"')
            {
                char nextChar = *++charPtr;
                if (nextChar == '"')
                {        // escaped double quote
                    *tokenBuffer++ = '"';
                } else {
                    *tokenBuffer = '\0';
                    charPtr--;
                    inString = -1;
                }
            } else {
              *tokenBuffer++ = *charPtr;
            }
        } else switch (*charPtr) {
            case '"' :
              inString = 0;
              break;
            case ',' :
              charPtr++;
              *tokenBuffer = '\0';
              return(charPtr);
            case '\t' :
            case '\n' :
            case '\r' :
              break;
            default :
              *tokenBuffer++ = *charPtr;
        }
        charPtr++;
    }
    *tokenBuffer = '\0';
    return(charPtr);
}
