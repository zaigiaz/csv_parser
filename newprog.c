#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_SEP ','
#define NEWLINE '\n'
#define BUF_SIZE 256

// TODO: Add Data into Array of Structs
// TODO: Add Helper Functions to convert to int or float if needed
// TODO: add some Asserts and test cases to ensure code reliability

struct fields {
  char name[BUF_SIZE];
  char age[BUF_SIZE];
  char date[BUF_SIZE];
  /* char EXAMPLE_FIELD[BUF_SIZE]; */
};

int main(void) {

  FILE *file = fopen("file.csv", "r");
  
  int lines=0;
  char c;

  // get number of lines in file
  while(!feof(file))
    {
      c = fgetc(file);
      if(c == NEWLINE)
	{
	  lines += 1;
	}
    }

  /* printf("Lines: %d\n", lines); */
  
  // array of fields that hold all data for CSV
  struct fields list[lines];
  
  char buffer[BUF_SIZE];
  buffer[0] = '\0';
  size_t len=0;

  // reset file pointer back to start of file
  fseek(file, 0, SEEK_SET);

  char ch;
  int list_count=0, count=0;

  while((ch = fgetc(file)) != EOF) {    

    if(ch == FIELD_SEP) {
      /* printf("\nhere is a field: %s", buffer); */

      // null terminating string must have terminator
      count += 1;
      buffer[len++] = '\0';

      switch(count) {
      case 1:
	/* logic here to strcpy buffer into struct field */
	strcpy(list[list_count].name, buffer);
	break;
      case 2:
	strcpy(list[list_count].age, buffer);
	break;      
      }
      
      buffer[0] = '\0';
      len = 0;
      continue;
    }

    if(ch == NEWLINE) {

      // only increment list 
      count = 0;

      /* printf("\nhere is a field: %s", buffer); */

      buffer[len++] = '\0';
      strcpy(list[list_count].date, buffer);
      buffer[0] = '\0';

      // reset buffer
      len = 0;

      list_count += 1;
      continue;
     }



    // build the string here
    buffer[len++] = ch;

  }

  printf("Here is the first field: %s", list[3].age);

  int close = fclose(file);
  if(close == EOF) { printf("error at closing"); exit(1); }  
}
