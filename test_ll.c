#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie_record.h"


void printMovieRecord(struct MovieRecord_Node *head);

int main(int argc, char** argv)
{
  // pointer to the head node of MovieRecord LL
  struct MovieRecord_Node** pHead_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node*));
  // declare and initialize the first (head) node of the LL
  struct MovieRecord_Node* head_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node));
  // assign the memory address to the head node to the pHead pointer-to-pointer to stuct MovieRecord_Node
  *pHead_MovieRecord_Node = head_MovieRecord_Node;

  // dereference the pointer-to-pointer of head MovieRecord_Node and allocate memory
  (*pHead_MovieRecord_Node)->record = malloc(sizeof(struct MovieRecord));
  // allocate memory for the pointer-to-pointer to the head MovieDataColumn_Node
  (*pHead_MovieRecord_Node)->record->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node*));
  // declare and initialize head_MovieDataColumn_Node
  struct MovieDataColumn_Node* head_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
  head_MovieDataColumn_Node->dataColumn = malloc(sizeof(struct MovieDataColumn));
  head_MovieDataColumn_Node->dataColumn->columnName = malloc(sizeof(char*)*strlen("color") + 1);
  head_MovieDataColumn_Node->dataColumn->columnName = "color";
  head_MovieDataColumn_Node->dataColumn->data = malloc(sizeof(struct MovieData));
  head_MovieDataColumn_Node->dataColumn->data->dataType = STRING;
  head_MovieDataColumn_Node->dataColumn->data->s = malloc(sizeof(char*)*strlen("black and white") + 1);
  head_MovieDataColumn_Node->dataColumn->data->s = "black and white";

  // assign pointer to point to the pointer of the head_MovieDataColumn_Node
  (*pHead_MovieRecord_Node)->record->pHead_MovieDataColumn_Node = &head_MovieDataColumn_Node;

  (*pHead_MovieRecord_Node)->next = malloc(sizeof(struct MovieRecord_Node));
  (*pHead_MovieRecord_Node)->next->record = malloc(sizeof(struct MovieRecord));
  struct MovieRecord* second_MovieRecord = malloc(sizeof(struct MovieRecord));
  (*pHead_MovieRecord_Node)->next->record = second_MovieRecord;
  second_MovieRecord->pHead_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node*));
  struct MovieDataColumn_Node* second_MovieRecord_head_MovieDataColumn_Node = malloc(sizeof(struct MovieDataColumn_Node));
  second_MovieRecord->pHead_MovieDataColumn_Node = &second_MovieRecord_head_MovieDataColumn_Node;
  second_MovieRecord_head_MovieDataColumn_Node->dataColumn = malloc(sizeof(struct MovieDataColumn));
  second_MovieRecord_head_MovieDataColumn_Node->dataColumn->columnName = malloc(sizeof(char*)*strlen("director") + 1);
  second_MovieRecord_head_MovieDataColumn_Node->dataColumn->columnName = "director";
  second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data = malloc(sizeof(struct MovieData));
  second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data->dataType = STRING;
  second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data->s = malloc(sizeof(char*)*strlen("James Cameron") + 1);
  second_MovieRecord_head_MovieDataColumn_Node->dataColumn->data->s = "James Cameron";

  struct MovieRecord_Node** pCurrent = malloc(sizeof(struct MovieRecord_Node*));
  (*pCurrent) = *pHead_MovieRecord_Node;
  printf("pCurrent columnName: %s\t data: %s\n", (*(*pCurrent)->record->pHead_MovieDataColumn_Node)->dataColumn->columnName, (*(*pCurrent)->record->pHead_MovieDataColumn_Node)->dataColumn->data->s);
  printf("pCurrent columnName: %s\t data: %s\n", (*((*pCurrent)->next)->record->pHead_MovieDataColumn_Node)->dataColumn->columnName, (*((*pCurrent)->next)->record->pHead_MovieDataColumn_Node)->dataColumn->data->s);

  /***********************
  ** GET COLUMN HEADERS **
  ***********************/
  char *lineBuffer = NULL;
  size_t lineLength = 0;
  int numberOfCharactersReadIn = 0;

  struct MovieRecordColumnHeader_Node** pHead_MovieRecordColumnHeader_Node = malloc(sizeof(struct MovieRecordColumnHeader_Node*));
  struct MovieRecordColumnHeader_Node* head_MovieRecordColumnHeader_Node = malloc(sizeof(struct MovieRecordColumnHeader_Node));
  // assign the memory address to the head node to the pHead pointer-to-pointer to stuct MovieRecordColumnHeader_Node
  *pHead_MovieRecordColumnHeader_Node = head_MovieRecordColumnHeader_Node;

  head_MovieRecordColumnHeader_Node->columnHeader = malloc(sizeof(struct MovieRecordColumnHeader));
  head_MovieRecordColumnHeader_Node->columnHeader->name = malloc(sizeof(char*)*strlen("color") + 1);
  head_MovieRecordColumnHeader_Node->columnHeader->name = "color";

  if ((numberOfCharactersReadIn = getline(&lineBuffer, &lineLength, stdin)) != -1)
  {

  }


  while((numberOfCharactersReadIn = getline(&lineBuffer, &lineLength, stdin)) != -1)
  {
    printf("length of line read in: %d\n", numberOfCharactersReadIn);
    printf("line read in: %s", lineBuffer);
  }

  return 0;
}
