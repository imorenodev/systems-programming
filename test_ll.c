#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie_record.h"

#define DELIMITER           ","

char *readToken(char *lineBuffer, char *tokenBuffer);
enum Type getType(char *columnHeaderIndex);
void printColumnHeaders(struct ColumnHeader_Node** head);
void printMovieRecords(struct MovieRecord_Node** head);
void printMovieDataColumns(struct MovieDataColumn_Node** head);
void printMovieDataColumns2(struct MovieDataColumn_Node* head);
void printDataColumn(struct MovieDataColumn** head);
struct ColumnHeader_Node* appendColumnHeaderNode(struct ColumnHeader_Node** head, char* value);
struct MovieRecord_Node* appendMovieRecordNode(struct MovieRecord_Node** head, struct MovieDataColumn_Node** movieDataColumnNode);
struct MovieDataColumn_Node* appendMovieDataColumnNode(struct MovieDataColumn_Node** head, struct MovieDataColumn** movieDataColumn);
struct MovieDataColumn* getMovieDataColumn(char** token, char** columnName);


int main(int argc, char** argv)
{
  char* lineBuffer = NULL;
  size_t lineLength = 0;
  size_t read = 0;
  int isHeaderRow = 0;
  char* token = malloc(sizeof(char*)*100);

  /*****************************************
  ** INITIALIZE COLUMN HEADER LL POINTER **
  *****************************************/
  struct ColumnHeader_Node* pHead_ColumnHeader_Node = NULL;
  struct MovieRecord_Node* pHead_MovieRecord_Node = NULL;

  // get first line of input (outside of the while loop) to handle the header column
  read = getline(&lineBuffer, &lineLength, stdin);
  while (read != -1)
  {
    if (isHeaderRow == 0) // get column headers
    {
      while (*lineBuffer)
      {
        lineBuffer = readToken(lineBuffer, token);
        appendColumnHeaderNode(&pHead_ColumnHeader_Node, token);
      }

      // DONE WITH HEADER COLUMNS
      // Read next line to prime for the
      // MovieRecord parsing on the next loop

      isHeaderRow = -1;
      lineBuffer = NULL;
      read = getline(&lineBuffer, &lineLength, stdin);

    }  else { // get MovieRecords


      //
      // printf("**HEAD/FIRST current_MovieDataColumn_Node: %p\n", current_MovieDataColumn_Node);
      // //set the record for the MovieRecord that is at the location currently pointed to by current_MovieRecord_Node
      // current_MovieRecord_Node->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
      // current_MovieRecord_Node->pHead_MovieDataColumn_Node->dataColumn = NULL;
      // printf("current_MovieRecord_Node->pHead_MovieDataColumn_Node->dataColumn: %p", current_MovieRecord_Node->pHead_MovieDataColumn_Node->dataColumn);
      // current_MovieRecord_Node->pHead_MovieDataColumn_Node->next = malloc(sizeof(struct MovieDataColumn_Node*));
      // current_MovieRecord_Node->pHead_MovieDataColumn_Node->next = current_MovieDataColumn_Node;
      //
      // point current_ColumnHeader_Node back to HEAD (start) of columnHeader LL
      // so we can loop through column header names and assign for each new MovieRecord MovieDataColumn
      //current_ColumnHeader_Node = pHead_ColumnHeader_Node->next;

      struct MovieDataColumn_Node* pHead_MovieDataColumn_Node = NULL;

      while (*lineBuffer)
      {
        //printf("**NEXT current_MovieDataColumn_Node: %p\n", current_MovieDataColumn_Node);
        lineBuffer = readToken(lineBuffer, token);

        char* columnName = "color";
        struct MovieDataColumn* tempMovieDataColumn = getMovieDataColumn(&token, &columnName);

        appendMovieDataColumnNode(&pHead_MovieDataColumn_Node, &tempMovieDataColumn);
        // char *columnName = malloc(sizeof(char) * (strlen(current_ColumnHeader_Node->value) + 1));
        // strcpy(columnName, current_ColumnHeader_Node->value);
        // if (current_ColumnHeader_Node->next != NULL) {
        //   current_ColumnHeader_Node = current_ColumnHeader_Node->next;
        // }
      }

      printMovieDataColumns2(pHead_MovieDataColumn_Node);
      printf("&pHead_MovieDataColumn_Node %p\n", &pHead_MovieDataColumn_Node);
      appendMovieRecordNode(&pHead_MovieRecord_Node, &pHead_MovieDataColumn_Node);

      // Finished with a MovieRecord, prime getLine for next iteration
      // and create and point to the next (new) MovieRecord Node
      read = getline(&lineBuffer, &lineLength, stdin);
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

  //current_ColumnHeader_Node = pHead_ColumnHeader_Node->next;
  printColumnHeaders(&pHead_ColumnHeader_Node);
  printMovieRecords(&pHead_MovieRecord_Node);


  // PRINT MOVIE RECORDS
/**
  printf("\nBEFORE PRINT MOVIE RECORDS\n");
      printf("\n\ncurrent_MovieRecord_Node %p\n", current_MovieRecord_Node);
  current_MovieRecord_Node = pHead_MovieRecord_Node->next;
      printf("current_MovieRecord_Node %p\n", current_MovieRecord_Node);
  printf("1. DESPERATE TEST %p\n", pHead_MovieRecord_Node);
  printf("2. DESPERATE TEST %p\n", pHead_MovieRecord_Node->pHead_MovieDataColumn_Node);
  printf("3. DESPERATE TEST %p\n", current_MovieRecord_Node);
  printf("4. DESPERATE TEST %p\n", current_MovieRecord_Node->pHead_MovieDataColumn_Node);
  ~~~~~> printf("5. DESPERATE TEST %p\n", current_MovieRecord_Node->pHead_MovieDataColumn_Node->dataColumn);
  printf("6. DESPERATE TEST %p\n", current_MovieRecord_Node->pHead_MovieDataColumn_Node->next);
  ~~~~~> printf("7. DESPERATE TEST %p\n", current_MovieRecord_Node->pHead_MovieDataColumn_Node->next->dataColumn);
  printf("8. DESPERATE TEST %p\n", current_MovieRecord_Node->next);
  printf("9. DESPERATE TEST %p\n", current_MovieRecord_Node->next->pHead_MovieDataColumn_Node->dataColumn);
  printf("10.DESPERATE TEST %p\n", current_MovieRecord_Node->next->next);
  printf("11.DESPERATE TEST %p\n", current_MovieRecord_Node->next->pHead_MovieDataColumn_Node->dataColumn);

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
**/
  return 0;
}

struct MovieDataColumn* getMovieDataColumn(char** token, char** columnName)
{
  struct MovieDataColumn* newMovieDataColumn = malloc(sizeof(struct MovieDataColumn));
  newMovieDataColumn->columnName = malloc(sizeof(char) * (strlen(*columnName) + 1));
  strcpy(newMovieDataColumn->columnName, *columnName);

  newMovieDataColumn->dataType = getType(*columnName);

  if (newMovieDataColumn->dataType == STRING) {
    newMovieDataColumn->s = malloc(sizeof(char) * (strlen(*token) + 1));
    strcpy(newMovieDataColumn->s, *token);
  } else if (newMovieDataColumn->dataType == FLOATS) {
    newMovieDataColumn->f = atof(*token);
  } else if (newMovieDataColumn->dataType == INTS) {
    newMovieDataColumn->i = atoi(*token);
  } else {
    fprintf(stderr, "Fatal Error: Invalid MovieData DataType");
    exit(0);
  }

  return newMovieDataColumn;
}

struct ColumnHeader_Node* appendColumnHeaderNode(struct ColumnHeader_Node** head, char* data)
{
  struct ColumnHeader_Node* newNode = (struct ColumnHeader_Node*)malloc(sizeof(struct ColumnHeader_Node));
  newNode->next = NULL;
  newNode->value = malloc(sizeof(char) * (strlen(data) + 1));
  strcpy(newNode->value, data);
  struct ColumnHeader_Node* temp = *head;

  if (temp == NULL)
    *head = newNode;
  else {
    while(temp->next)
      temp = temp->next;
      temp->next = newNode;
  }

  return newNode;
}


struct MovieDataColumn_Node* appendMovieDataColumnNode(struct MovieDataColumn_Node** head, struct MovieDataColumn** data)
{
  struct MovieDataColumn_Node* newNode = (struct MovieDataColumn_Node*)malloc(sizeof(struct MovieDataColumn_Node));
  newNode->next = NULL;
  newNode->dataColumn = malloc(sizeof(struct MovieDataColumn));
  // TODO
  newNode->dataColumn = *data;

  struct MovieDataColumn_Node* temp = *head;

  if (temp == NULL)
    *head = newNode;
  else {
    while(temp->next)
      temp = temp->next;
      temp->next = newNode;
  }

  return newNode;
}

struct MovieRecord_Node* appendMovieRecordNode(struct MovieRecord_Node** head, struct MovieDataColumn_Node** data)
{
  struct MovieRecord_Node* newNode = (struct MovieRecord_Node*)malloc(sizeof(struct MovieRecord_Node));
  newNode->next = NULL;
  newNode->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
  // TODO
  newNode->pHead_MovieDataColumn_Node = *data;

  struct MovieRecord_Node* temp = *head;

  if (temp == NULL)
    *head = newNode;
  else {
    while(temp->next)
      temp = temp->next;
      temp->next = newNode;
  }

  return newNode;
}

void printColumnHeaders(struct ColumnHeader_Node** head)
{
  struct ColumnHeader_Node* temp = *head;

  while (temp != NULL)
  {
    printf("%s\n", temp->value);
    if (temp->next != NULL)
    {
      temp = temp->next;
    } else {
      break;
    }
  }

}

void printMovieRecords(struct MovieRecord_Node** head)
{
  struct MovieRecord_Node* temp = *head;

  while (temp != NULL)
  {
    printMovieDataColumns(&(temp->pHead_MovieDataColumn_Node));

    if (temp->next != NULL)
    {
      temp = temp->next;
    } else {
      break;
    }
  }

}

void printMovieDataColumns(struct MovieDataColumn_Node** head)
{
  struct MovieDataColumn_Node* temp = *head;

  while (temp != NULL)
  {
    printDataColumn(&(temp->dataColumn));

    if (temp->next != NULL)
    {
      temp = temp->next;
    } else {
      break;
    }
  }

}

void printDataColumn(struct MovieDataColumn** head)
{
  struct MovieDataColumn* temp = *head;

  if (temp != NULL)
  {
    if (temp->dataType == STRING)
      printf("columnName: %s, data: %s\n", temp->columnName, temp->s);
    else if (temp->dataType == INTS)
      printf("columnName: %s, data: %d\n", temp->columnName, temp->i);
    else if (temp->dataType == FLOATS)
      printf("columnName: %s, data: %lf\n", temp->columnName, temp->f);
    else {
      fprintf(stderr, "Fatal Error:\t Invalid DataType.");
      exit(0);
    }
  }

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
