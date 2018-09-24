#ifndef SIMPLE_CSV_SORTER_H
#define SIMPLE_CSV_SORTER_H

#define DEBUGGING           "**DEBUGGING**\t"
#define DELIMITER           ","
#define MAX_LINE_LENGTH     512
#define MAX_NUM_RECORDS     5050
#define MAX_NUM_COLUMNS     30


/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

struct MovieRecord {
  char  *color;
  char  *director_name;
  int   num_critic_for_reviews;
  int   duration;
  int   director_facebook_likes;
  int   actor_3_facebook_likes;
  char* actor_2_name;
  int   actor_1_facebook_likes;
  int   gross;
  char  *genres;
  char  *actor_1_name;
  char  *movie_title;
  int   num_voted_users;
  int   cast_total_facebook_likes;
  char  *actor_3_name;
  int   facenumber_in_poster;
  char  *plot_keywords;
  char  *movie_imdb_link;
  int   num_user_for_reviews;
  char  *language;
  char  *country;
  char  *content_rating;
  int   budget;
  int   title_year;
  int   actor_2_facebook_likes;
  float imdb_score;
  float aspect_ratio;
  int   movie_facebook_likes;
};

void printArguments(int argCount, char *argArray[]);
void printMovieRecords(int count, char **arrayOfColumnNames, struct MovieRecord **arrayOfMovieRecords);
void getArrayOfTokens(char **arrayOfTokens, char * line, const char *delimiter);
int getLine(char line[], int maxLength);
void initializeArrayOfMovies(int numberOfRecords, struct MovieRecord **arrayOfMovies);
void mergeSort(int count, const char *columnName, struct MovieRecord **sourceArray, struct MovieRecord **outputArray); 
void merge(int count1, const char *columnName, struct MovieRecord **tempArray1, int count2, struct MovieRecord **tempArray2, struct MovieRecord **outputArray);
void copyArrayOfMovies(int count, struct MovieRecord **overSizedArray, struct MovieRecord **correctSizeArray);
int isValidArguments(int argc, char **argv);

#endif
