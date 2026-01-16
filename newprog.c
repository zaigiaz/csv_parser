#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FIELD_SEP ','
#define NEWLINE '\n'
#define BUF_SIZE 256

// TODO: Add Helper Functions to convert to int or float if needed
// TODO: use isdigit() and other function to have better functionality

struct fields {
  char name[BUF_SIZE];
  char age[BUF_SIZE];
  char date[BUF_SIZE];
  /* char EXAMPLE_FIELD[BUF_SIZE]; */
};


// print all the rows in CSV
void print_file(struct fields list[BUF_SIZE], int lines) {  
  printf("\nPrinting out All Fields | Debug\n\n");

  for(int i=0; i<lines; i++) {
    printf("-------------\n");
    printf("%s\n", list[i].name);
    printf("%s\n", list[i].age);
    printf("%s\n", list[i].date);
  }  
}

// get # of lines in csv file, could change by subtracting one if csv has header defining fields
int getNumberItems(FILE *file) {
  int lines=0;
  char c;

  while(!feof(file))
    {
      c = fgetc(file);
      if(c == NEWLINE)
	{
	  lines += 1;
	}
    }
  assert(lines > 0);

  return lines;
}


 int main(void) {

  FILE *file = fopen("file.csv", "r");
    if(file == NULL) {
    perror("file pointer for provided csv is null");
  }

  int lines=0;

  // get number of lines in file
  lines = getNumberItems(file);
  
  // array of fields that hold all data for CSV
  struct fields list[lines];
  
  char buffer[BUF_SIZE];
  buffer[0] = '\0';
  size_t len=0;

  // reset file pointer back to start of file
  fseek(file, 0, SEEK_SET);

  char ch;
  int row_count=0, char_point=0;

  while((ch = fgetc(file)) != EOF) {    

    if(ch == FIELD_SEP) {
      // null terminating string must have terminator
      char_point += 1;
      buffer[len++] = '\0';

      switch(char_point) {
      case 1:
	strcpy(list[row_count].name, buffer);
	break;
      case 2:
	strcpy(list[row_count].age, buffer);
	break;      
      }
      
      buffer[0] = '\0';
      len = 0;

      continue;
    }

    if(ch == NEWLINE) {
      // only increment list 
      char_point = 0;

      buffer[len++] = '\0';
      strcpy(list[row_count].date, buffer);
      buffer[0] = '\0';

      // reset buffer length
      len = 0;
      row_count += 1;

      continue;
     }

    // build the string here
    buffer[len++] = ch;
  }

  // print all rows in csv
  print_file(list, lines);
  
  int close = fclose(file);
  if(close == EOF) { perror("error at closing"); }
}
