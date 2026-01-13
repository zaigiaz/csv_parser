#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_SEP ','
#define NEWLINE '\n'

struct fields {
  char *name;
  char *age;
  char *date;
};

int main(void) {

  FILE *file = fopen("file.csv", "r");
  
  int lines=0;
  char c;

  // get number of lines in file
  while(!feof(file))
    {
      c = fgetc(file);
      if(c == '\n')
	{
	  lines += 1;
	}
    }


  printf("Lines: %d\n", lines);
  struct fields list[lines];
  char buffer[256];
  size_t len;

  // reset file pointer back to start of file
  fseek(file, 0, SEEK_SET);

  char ch; 
  int field_count=0;

  while((ch = fgetc(file)) != EOF) {    

    if(ch == FIELD_SEP) {

      printf("\nhere is a field: %s", buffer);

      /* switch(field_count) { */
      /* case 1: */
      /* 	lines[counter].name = build; */
      /* case 2: */
      /* 	lines[counter].age = build; */
      /* case 3: */
      /* 	lines[counter].date = build; */
      /* } */

      field_count += 1;
      continue;
    }

    if(ch == NEWLINE) {
      /* counter += 1; */
      printf("\nhere is a field: %s", buffer);
      buffer[0] = '\0';
      continue;
     }

    // build the string here
    buffer[len++] = (char)c;
    

  printf("%c", ch);
  }

  printf("\nfield_count: %d", field_count);
  int close = fclose(file);
  if(close == EOF) { printf("error at closing"); exit(1); }

  printf("\n\nhello from end of function");
}


