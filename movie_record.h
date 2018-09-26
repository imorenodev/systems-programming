#ifndef MOVIE_RECORD
#define MOVIE_RECORD


enum Type { INTS, FLOATS, STRING };

struct MovieData {
  enum Type dataType;
  int i;
  float f;
  char* s;
};

struct MovieDataColumn {
  char* columnName;
  struct MovieData* data;
};

struct MovieDataColumn_Node {
  //MovieDataColumn data
  struct MovieDataColumn* dataColumn;
  // pointer to next node in the Linked List of MovieRecord DataColumn
  struct MovieDataColumn_Node* next;
};

struct MovieRecord {
  // pointer-to-pointer to first MovieDataColumn_Node in the LL
  struct MovieDataColumn_Node** pHead_MovieDataColumn_Node;
};

struct MovieRecord_Node {
  // MovieRecord data
  struct MovieRecord* record;
  // pointer to next node in the Linked List of MovieRecords
  struct MovieRecord_Node* next;
};

struct MovieRecordColumnHeader {
  char* name;
};

struct MovieRecordColumnHeader_Node {
  // MovieRecord data
  struct MovieRecordColumnHeader* columnHeader;
  // pointer to next node in the Linked List of MovieRecords
  struct MovieRecordColumnHeader_Node* next;
};


#endif
