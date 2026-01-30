/* Program created by zaigiaz - 2026  */
/* edit the fields, and convert function to tailor towards your csv schema */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/array.h"

#define FIELD_SEP ','
#define NEWLINE '\n'

// TODO: add functionality to read first line of my schema
// TODO: and add automatic type_checking maybe instead of using schema
// TODO: fix floating point shenanigans

// TODO: change so that we push struct and call convert only once when we get to a newline
//       rather than calling it row_count amount of times

int main(void) {

  FILE *file = fopen("file.csv", "r");
    if(file == NULL) {
    perror("file pointer for provided csv is null");
  }

  fseek(file, 0, SEEK_SET);
  
  Array list;
  init(&list);

  char buffer[BUF_SIZE];
  buffer[0] = '\0';
  size_t len=0;

  char ch;
  int row_count=0, char_point=0;

  // item that we are pushing into array
  struct fields item;

  while((ch = fgetc(file)) != EOF) {    

    // parse header right here
    if(row_count == 0) {  }

    if(ch == FIELD_SEP) {
      char_point += 1;
      buffer[len++] = '\0';
      
      item = convert(item, char_point, buffer);

      buffer[0] = '\0';
      len = 0;

      continue;
    }

    if(ch == NEWLINE) {
      char_point += 1;
      buffer[len++] = '\0';

      item = convert(item, char_point, buffer);
      add(&list, item);

      buffer[0] = '\0';
      
      char_point = 0;
      len        = 0;
      row_count += 1;
      continue;
     }

    buffer[len++] = ch;
  }


  print_csv(&list);
  freeArray(&list);
  int close = fclose(file);
  if(close == EOF) { perror("error at closing"); }
}
