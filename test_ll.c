#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie_record.h"

#define DELIMITER           ","

void printMovieRecord(struct MovieRecord_Node *head);
void getTokens(struct MovieRecordColumnHeader_Node** pHead, char* line, const char* delimiter);
char *readToken(char *line, char *buf);
enum Type getType(int columnHeaderIndex);


int main(int argc, char** argv)
{
  // // pointer to the head node of MovieRecord LL
  // struct MovieRecord_Node** pHead_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node*));
  // // declare and initialize the first (head) node of the LL
  // struct MovieRecord_Node* head_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node));
  // // assign the memory address to the head node to the pHead pointer-to-pointer to stuct MovieRecord_Node
  // *pHead_MovieRecord_Node = head_MovieRecord_Node;
  //
  // // dereference the pointer-to-pointer of head MovieRecord_Node and allocate memory
  // (*pHead_MovieRecord_Node)->record = malloc(sizeof(struct MovieRecord));
  // // allocate memory for the pointer-to-pointer to the head MovieDataColumn_Node
  // (*pHead_MovieRecord_Node)->record->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node*));
  // // declare and initialize head_MovieDataColumn_Node
  // struct MovieDataColumn_Node* head_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
  // head_MovieDataColumn_Node->dataColumn = malloc(sizeof(struct MovieDataColumn));
  // head_MovieDataColumn_Node->dataColumn->columnName = malloc(sizeof(char*)*strlen("color") + 1);
  // head_MovieDataColumn_Node->dataColumn->columnName = "color";
  // head_MovieDataColumn_Node->dataColumn->data = malloc(sizeof(struct MovieData));
  // head_MovieDataColumn_Node->dataColumn->data->dataType = STRING;
  // head_MovieDataColumn_Node->dataColumn->data->s = malloc(sizeof(char*)*strlen("black and white") + 1);
  // head_MovieDataColumn_Node->dataColumn->data->s = "black and white";
  //
  // // assign pointer to point to the pointer of the head_MovieDataColumn_Node
  // (*pHead_MovieRecord_Node)->record->pHead_MovieDataColumn_Node = &head_MovieDataColumn_Node;
  //
  // (*pHead_MovieRecord_Node)->next = malloc(sizeof(struct MovieRecord_Node));
  // (*pHead_MovieRecord_Node)->next->record = malloc(sizeof(struct MovieRecord));
  // struct MovieRecord* second_MovieRecord = malloc(sizeof(struct MovieRecord));
  // (*pHead_MovieRecord_Node)->next->record = second_MovieRecord;
  // second_MovieRecord->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node*));
  // struct MovieDataColumn_Node* second_MovieRecord_head_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
  // second_MovieRecord->pHead_MovieDataColumn_Node = &second_MovieRecord_head_MovieDataColumn_Node;
  // second_MovieRecord_head_MovieDataColumn_Node->dataColumn = malloc(sizeof(struct MovieDataColumn));
  // second_MovieRecord_head_MovieDataColumn_Node->dataColumn->columnName = malloc(sizeof(char*)*strlen("director") + 1);
  // second_MovieRecord_head_MovieDataColumn_Node->dataColumn->columnName = "director";
  // second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data = malloc(sizeof(struct MovieData));
  // second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data->dataType = STRING;
  // second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data->s = malloc(sizeof(char*)*strlen("James Cameron") + 1);
  // second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data->s = "James Cameron";
  //
  // struct MovieRecord_Node** pCurrent = malloc(sizeof(struct MovieRecord_Node*));
  // (*pCurrent) = *pHead_MovieRecord_Node;
  // printf("pCurrent columnName: %s\t data: %s\n", (*(*pCurrent)->record->pHead_MovieDataColumn_Node)->dataColumn->columnName, (*(*pCurrent)->record->pHead_MovieDataColumn_Node)->dataColumn->data->s);
  // printf("pCurrent columnName: %s\t data: %s\n", (*((*pCurrent)->next)->record->pHead_MovieDataColumn_Node)->dataColumn->columnName, (*((*pCurrent)->next)->record->pHead_MovieDataColumn_Node)->dataColumn->data->s);

  /***********************
  ** GET COLUMN HEADERS **
  ***********************/
  char *lineBuffer = NULL;
  size_t lineLength = 0;
  int numberOfCharactersReadIn = 0;
  int numberOfColumns = 0;

  // pointer to keep track of first MovieRecordColumnHeader_Node in the LL
  struct MovieRecordColumnHeader_Node** pHead_MovieRecordColumnHeader_Node = malloc(sizeof(struct MovieRecordColumnHeader_Node*));
  struct MovieRecordColumnHeader_Node* current_MovieRecordColumnHeader_Node = malloc(sizeof(struct MovieRecordColumnHeader_Node));
  // assign the memory address to the head node to the pHead pointer-to-pointer to stuct MovieRecordColumnHeader_Node
  *pHead_MovieRecordColumnHeader_Node = current_MovieRecordColumnHeader_Node;

  if ((numberOfCharactersReadIn = getline(&lineBuffer, &lineLength, stdin)) != -1)
  {
    char* token = malloc(sizeof(char*)*100);

    while (*lineBuffer)
    {
      lineBuffer = readToken(lineBuffer, token);

      //for the MovieRecordColumnHeader that is at the location currently pointed to by current_MovieRecordColumnHeader_Node
      //set it's columnHeader's name
      current_MovieRecordColumnHeader_Node->columnHeader = malloc(sizeof(struct MovieRecordColumnHeader));
      current_MovieRecordColumnHeader_Node->columnHeader->name = malloc(sizeof(char*) * (strlen(token) + 1));
      strcpy(current_MovieRecordColumnHeader_Node->columnHeader->name, token);
      current_MovieRecordColumnHeader_Node->next = NULL;

      // if there are still tokens left to process, then create a new MovieRecordColumnHeader_Node and append to LL
      if (lineBuffer != NULL)
      {
        // allocate memory for a new MovieRecordColumnHeader_Node and store it's address in tempMovieRecordColumnHeader_Node
        struct MovieRecordColumnHeader_Node* tempMovieRecordColumnHeader_Node = malloc(sizeof(struct MovieRecordColumnHeader_Node));
        // for the MovieRecordColumnHeader that is at the location currently pointed to by current_MovieRecordColumnHeader_Node
        // set it's next node to point to the address of the new MovieRecordColumnHeader_Node pointed to by tempMovieRecordColumnHeader_Node
        current_MovieRecordColumnHeader_Node->next = tempMovieRecordColumnHeader_Node;
        // now assign the pointer variable named current_MovieRecordColumnHeader_Node the new address stored in tempMovieRecordColumnHeader_Node
        current_MovieRecordColumnHeader_Node = tempMovieRecordColumnHeader_Node;
        numberOfColumns++;
      }

    }

  }


  char *columnHeaderArray[numberOfColumns];
  /*************************
  ** PRINT COLUMN HEADERS **
  *************************/
  struct MovieRecordColumnHeader_Node* curr_MovieRecordColumnHeader_Node = malloc(sizeof(struct MovieRecordColumnHeader_Node));
  curr_MovieRecordColumnHeader_Node = *pHead_MovieRecordColumnHeader_Node;
  int index = 0;

  while (curr_MovieRecordColumnHeader_Node->columnHeader != NULL)
  {
    //printf("curr_MovieRecordColumnHeader_Node: %s\n", curr_MovieRecordColumnHeader_Node->columnHeader->name);

    columnHeaderArray[index] = curr_MovieRecordColumnHeader_Node->columnHeader->name;

    if (curr_MovieRecordColumnHeader_Node->next != NULL)
    {
      curr_MovieRecordColumnHeader_Node = curr_MovieRecordColumnHeader_Node->next;
      index++;
    } else {
      break;
    }
  }

  while((numberOfCharactersReadIn = getline(&lineBuffer, &lineLength, stdin)) != -1)
  {
    //printf("length of line read in: %d\n", numberOfCharactersReadIn);
    //printf("line read in: %s", lineBuffer);
  }


  /*********************
  ** GET MovieRecords **
  *********************/


  // pointer to keep track of first MovieRecord_Node in the LL
  struct MovieRecord_Node** pHead_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node*));
  struct MovieRecord_Node* current_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node));
  // assign the memory address to the head node to the pHead pointer-to-pointer to stuct MovieRecord_Node
  *pHead_MovieRecord_Node = current_MovieRecord_Node;

  printf("lineBuffer: %s\tlineLength: %d\t\n%s\n", lineBuffer, (int)lineLength, stdin);
  // for each remaining line of input from stdin we create a new MovieRecord_Node, populate it's data and append to end of LL
  if ((numberOfCharactersReadIn = getline(&lineBuffer, &lineLength, stdin)) != -1)
  {
    printf("inside get movie records: %p\n", pHead_MovieRecord_Node);
    //for the MovieRecord that is at the location currently pointed to by current_MovieRecord_Node
    //set it's record
    current_MovieRecord_Node->record = malloc(sizeof(struct MovieRecord));
    current_MovieRecord_Node->record->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node*));
    // initialize the head MovieDataColumn_Node
    struct MovieDataColumn_Node* current_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
    // assign the memory address of the head node to the pHead pointer-to-pointer to stuct MovieDataColumn_Node
    (*current_MovieRecord_Node->record->pHead_MovieDataColumn_Node) = current_MovieDataColumn_Node;

    char* token = malloc(sizeof(char*)*100);
    int columnHeaderIndex = 0;

    while (*lineBuffer)
    {
      printf("\nlineBuffer: %s\n", lineBuffer);
      lineBuffer = readToken(lineBuffer, token);
      printf("token: %s\n", token);

      current_MovieDataColumn_Node->dataColumn = malloc(sizeof(struct MovieDataColumn));
      current_MovieDataColumn_Node->dataColumn->columnName = malloc(sizeof(char*) * (strlen(columnHeaderArray[columnHeaderIndex]) + 1));
      strcpy(current_MovieDataColumn_Node->dataColumn->columnName, columnHeaderArray[columnHeaderIndex]);
      columnHeaderIndex++;

      current_MovieDataColumn_Node->dataColumn->data = malloc(sizeof(struct MovieData));
      current_MovieDataColumn_Node->dataColumn->data->dataType = getType(columnHeaderIndex);

      if (current_MovieDataColumn_Node->dataColumn->data->dataType == STRING)
      {
        current_MovieDataColumn_Node->dataColumn->data->s = malloc(sizeof(char*) * (strlen(token) + 1));
        strcpy(current_MovieDataColumn_Node->dataColumn->data->s, token);
      } else if (current_MovieDataColumn_Node->dataColumn->data->dataType == FLOATS) {
        //TODO
      } else if (current_MovieDataColumn_Node->dataColumn->data->dataType == INTS) {
        //TODO
      } else {
        fprintf(stderr, "Fatal Error: Invalid MovieData DataType");
        exit(0);
      }

      current_MovieDataColumn_Node->next = NULL;

      // if there are still tokens left to process, then create a new MovieDataColumn_Node and append to LL
      if (lineBuffer != NULL)
      {
        // allocate memory for a new MovieDataColumn_Node and store it's address in tempMovieDataColumn_Node
        struct MovieDataColumn_Node* tempMovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
        // for the MovieDataColumn that is at the location currently pointed to by current_MovieDataColumn_Node
        // set it's next node to point to the address of the new MovieDataColumn_Node pointed to by tempMovieDataColumn_Node
        current_MovieDataColumn_Node->next = tempMovieDataColumn_Node;
        // now assign the pointer variable named current_MovieDataColumn_Node the new address stored in tempMovieDataColumn_Node
        current_MovieDataColumn_Node = tempMovieDataColumn_Node;
      }

    }

  }



  return 0;
}

enum Type getType(int columnHeaderIndex)
{
  return STRING;
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

void getTokens(struct MovieRecordColumnHeader_Node** pHead, char* line, const char* delimiter)
{
    return;
}
