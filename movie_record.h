#ifndef MOVIE_RECORD
#define MOVIE_RECORD


enum Type { INTS, FLOATS, STRING };

struct MovieDataColumn {
  char* columnName;
  enum Type dataType;
  int i;
  float f;
  char* s;
};

struct MovieDataColumn_Node {
  //MovieDataColumn data
  struct MovieDataColumn* dataColumn;
  // pointer to next node in the Linked List of MovieRecord DataColumn
  struct MovieDataColumn_Node* next;
};

struct MovieRecord_Node {
  // pointer to first MovieDataColumn_Node in the LL
  struct MovieDataColumn_Node* pHead_MovieDataColumn_Node;
  // pointer to next node in the Linked List of MovieRecords
  struct MovieRecord_Node* next;
};

struct ColumnHeader_Node {
  // Column Name
  char* value;
  // pointer to next node in the Linked List of ColumnHeader_Nodes
  struct ColumnHeader_Node* next;
};


#endif
