#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FIELD_SEP ','
#define NEWLINE '\n'
#define BUF_SIZE 256

// TODO: use atoi() and atof() to convert strings to floats and integers
// TODO: add functionality to read first line of my schema

struct fields {
  char name[BUF_SIZE];
  int age;
  char date[BUF_SIZE];
  /* char EXAMPLE_FIELD[BUF_SIZE]; */
};


// print all the rows in CSV
void print_file(struct fields list[BUF_SIZE], int lines) {  
  printf("\nPrinting out All Fields | Debug\n\n");

  for(int i=0; i<lines; i++) {
    printf("-------------\n");
    printf("%s\n", list[i].name);
    printf("%d\n", list[i].age);
    printf("%s\n", list[i].date);
  }  
}


// get number of lines in file
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

  lines = getNumberItems(file);
  
  struct fields list[lines];

  char buffer[BUF_SIZE];
  buffer[0] = '\0';
  size_t len=0;

  fseek(file, 0, SEEK_SET);

  char ch;
  int row_count=0, char_point=0;

  while((ch = fgetc(file)) != EOF) {    

    if(ch == FIELD_SEP) {
      char_point += 1;
      buffer[len++] = '\0';
      // convert function here 

      switch(char_point) {
      case 1:
	strcpy(list[row_count].name, buffer);
	break;
      case 2:
	char *bptr = buffer;
	list[row_count].age = atoi(bptr);
	break;      
      }
      
      buffer[0] = '\0';
      len = 0;

      continue;
    }

    if(ch == NEWLINE) {
      char_point = 0;

      // have convert function here
      buffer[len++] = '\0';
      strcpy(list[row_count].date, buffer);
      buffer[0] = '\0';
      
      len = 0;
      row_count += 1;
      continue;
     }

    buffer[len++] = ch;
  }

  print_file(list, lines); 
  int close = fclose(file);
  if(close == EOF) { perror("error at closing"); }
}
