/* Program created by zaigiaz - 2026  */
/* edit the fields, and convert function to tailor towards your csv schema */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FIELD_SEP ','
#define NEWLINE '\n'
#define BUF_SIZE 256

// TODO: add functionality to read first line of my schema
// TODO: and add automatic type_checking maybe instead of using schema

struct fields {
  char name[BUF_SIZE];
  int age;
  float number;
  /* char EXAMPLE_FIELD[BUF_SIZE]; */
};

struct fields convert(struct fields item, int char_point, char buffer[BUF_SIZE]) {
  
  switch(char_point) {
  case 1:
    strcpy(item.name, buffer);
    break;
  case 2:
    char *bptr = buffer;
    item.age = atoi(bptr);
    break;
  case 3:
    char *fptr = buffer;
    item.number = atof(fptr);
    break;
  }

  return item;
}

// print all the rows in CSV
void print_file(struct fields list[], int lines) {  
  printf("\nPrinting out All Fields | Debug\n\n");

  for(int i=0; i<lines; i++) {
    printf("-------------\n");
    printf("%s\n", list[i].name);
    printf("%d\n", list[i].age);
    printf("%f\n", list[i].number);
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
  fseek(file, 0, SEEK_SET);
  
  struct fields list[lines];

  char buffer[BUF_SIZE];
  buffer[0] = '\0';
  size_t len=0;


  char ch;
  int row_count=0, char_point=0;

  while((ch = fgetc(file)) != EOF) {    

    // parse header right here
    if(row_count == 0) {

    }


    if(ch == FIELD_SEP) {
      char_point += 1;
      buffer[len++] = '\0';

      // convert function here 
      list[row_count] = convert(list[row_count], char_point, buffer);
      
      buffer[0] = '\0';
      len = 0;

      continue;
    }

    if(ch == NEWLINE) {
      char_point += 1;
      buffer[len++] = '\0';

      // have convert function here
      list[row_count] = convert(list[row_count], char_point, buffer);

      buffer[0] = '\0';
      
      char_point = 0;
      len        = 0;
      row_count += 1;
      continue;
     }

    buffer[len++] = ch;
  }

  print_file(list, lines);
  int close = fclose(file);
  if(close == EOF) { perror("error at closing"); }
}
