#include <stdio.h>
#include <stdlib.h>
#include <string.h>



enum Type { INTS, FLOATS, STRING };

struct MovieData {
  enum Type dataType;
  int i;
  float f;
  char* s;
};

struct MovieDataPoint {
  char* columnName;
  struct MovieData* data;
};

struct MovieDataPoint_Node {
  //MovieDataPoint data
  struct MovieDataPoint* dataPoint;
  // pointer to next node in the Linked List of MovieRecord DataPoints
  struct MovieDataPoint_Node* next;
};

struct MovieRecord {
  // pointer-to-pointer to first MovieDataPoint_Node in the LL
  struct MovieDataPoint_Node** pHead;
};

struct MovieRecord_Node {
  // MovieRecord data
  struct MovieRecord* record;
  // pointer to next node in the Linked List of MovieRecords
  struct MovieRecord_Node* next;
};

void printMovieRecord(struct MovieRecord_Node *head);

int main(int argc, char** argv)
{
  // pointer to the head node of MovieRecord LL
  struct MovieRecord_Node** pHead = malloc(sizeof(struct MovieRecord_Node*));
  // declare and initialize the first (head) node of the LL
  struct MovieRecord_Node* head_MovieRecord_Node = malloc(sizeof(struct MovieRecord_Node));
  // assign the memory address to the head node to the pHead pointer-to-pointer to stuct MovieRecord_Node
  *pHead = head_MovieRecord_Node;

  // dereference the pointer-to-pointer of head MovieRecord_Node and allocate memory
  (*pHead)->record = malloc(sizeof(struct MovieRecord));
  // allocate memory for the pointer-to-pointer to the head MovieDataPoint_Node
  (*pHead)->record->pHead = malloc(sizeof(struct MovieDataPoint_Node*));
  // declare and initialize head_MovieDataPoint_Node
  struct MovieDataPoint_Node* head_MovieDataPoint_Node = malloc(sizeof(struct MovieDataPoint_Node));
  head_MovieDataPoint_Node->dataPoint = malloc(sizeof(struct MovieDataPoint));
  head_MovieDataPoint_Node->dataPoint->columnName = malloc(sizeof(char*)*strlen("color") + 1);
  head_MovieDataPoint_Node->dataPoint->columnName = "color";
  head_MovieDataPoint_Node->dataPoint->data = malloc(sizeof(struct MovieData));
  head_MovieDataPoint_Node->dataPoint->data->dataType = STRING;
  head_MovieDataPoint_Node->dataPoint->data->s = malloc(sizeof(char*)*strlen("black and white") + 1);
  head_MovieDataPoint_Node->dataPoint->data->s = "black and white";

  // assign pointer to point to the pointer of the head_MovieDataPoint_Node
  (*pHead)->record->pHead = &head_MovieDataPoint_Node;

  (*pHead)->next = malloc(sizeof(struct MovieRecord_Node));
  (*pHead)->next->record = malloc(sizeof(struct MovieRecord));
  struct MovieRecord* second_MovieRecord = malloc(sizeof(struct MovieRecord));
  (*pHead)->next->record = second_MovieRecord;
  second_MovieRecord->pHead = malloc(sizeof(struct MovieDataPoint_Node*));
  struct MovieDataPoint_Node* second_MovieRecord_head_MovieDataPoint_Node = malloc(sizeof(struct MovieDataPoint_Node));
  second_MovieRecord->pHead = &second_MovieRecord_head_MovieDataPoint_Node;
  second_MovieRecord_head_MovieDataPoint_Node->dataPoint = malloc(sizeof(struct MovieDataPoint));
  second_MovieRecord_head_MovieDataPoint_Node->dataPoint->columnName = malloc(sizeof(char*)*strlen("director") + 1);
  second_MovieRecord_head_MovieDataPoint_Node->dataPoint->columnName = "director";
  second_MovieRecord_head_MovieDataPoint_Node->dataPoint->data = malloc(sizeof(struct MovieData));
  second_MovieRecord_head_MovieDataPoint_Node->dataPoint->data->dataType = STRING;
  second_MovieRecord_head_MovieDataPoint_Node->dataPoint->data->s = malloc(sizeof(char*)*strlen("James Cameron") + 1);
  second_MovieRecord_head_MovieDataPoint_Node->dataPoint->data->s = "James Cameron";

  struct MovieRecord_Node** pCurrent = malloc(sizeof(struct MovieRecord_Node*));
  (*pCurrent) = *pHead;
  printf("pCurrent columnName: %s\t data: %s\n", (*(*pCurrent)->record->pHead)->dataPoint->columnName, (*(*pCurrent)->record->pHead)->dataPoint->data->s);
  printf("pCurrent columnName: %s\t data: %s\n", (*((*pCurrent)->next)->record->pHead)->dataPoint->columnName, (*((*pCurrent)->next)->record->pHead)->dataPoint->data->s);
  //(*pCurrent) = (*pCurrent)->next;
  //printf("pCurrent columnName: %s\t data: %s", (*(*pCurrent)->record->pHead)->dataPoint->columnName, (*(*pCurrent)->record->pHead)->dataPoint->data->s);


  // struct MovieRecord_Node* tempNode = malloc(sizeof(struct MovieRecord_Node));
  // //head->next = malloc(sizeof(struct MovieRecord_Node));
  // head->next = tempNode;
  // head->next->record = malloc(sizeof(struct MovieRecord));
  // head->next->record->head = malloc(sizeof(struct MovieDataPoint_Node));
  // head->next->record->head->dataPoint = malloc(sizeof(struct MovieDataPoint));
  // head->next->record->head->dataPoint->columnName = malloc(sizeof(char*)*strlen("color"));
  // head->next->record->head->dataPoint->columnName = "color";
  // head->next->record->head->dataPoint->data = malloc(sizeof(struct MovieData));
  // head->next->record->head->dataPoint->data->dataType = STRING;
  // head->next->record->head->dataPoint->data->s = malloc(sizeof(char*)*strlen("black and white"));
  // head->next->record->head->dataPoint->data->s = "black and white";
  // head->next->record->
  //

  return 0;
}
