#ifndef MOVIE_RECORD
#define MOVIE_RECORD

enum Type { INTS, FLOATS, STRING }

typedef struct Data {
  Type s_type;
  int i;
  float f;
  char* s;
} Data_T;

typedef struct MovieDataPoint {
  char* columnName;
  struct Data_T* data;
} MovieDataPoint_T;

typdef struct MovieDataPoint_Node {
  //MovieDataPoint data
  MovieDataPoint_T dataPoint;
  // pointer to next node in the Linked List of MovieRecord DataPoints
  struct MovieDataPoint_Node_T* next;
} MovieDataPoint_Node_T;

typdef struct MovieRecord {
  struct MovieDataPoint_Node_T* next
} MovieRecord_T;

typedef struct MovieRecord_Node {
  // MovieRecord data
  MovieRecord_T record;
  // pointer to next node in the Linked List of MovieRecords
  struct MovieRecord_Node* next;
} MovieRecord_Node_T;


#endif
