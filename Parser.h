#ifndef PARSER_H
#define PARSER_H

#define SEPERATOR ','
#define ENDL '\n'

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256

// structure of information being parsed <placeholder>
struct info {
  char name[BUF_SIZE];
  char birth_date[BUF_SIZE];
  char address[BUF_SIZE];
};

void parse_file() {

  struct info parsed;


  strcpy(parsed.name, "Jonathan");
  strcpy(parsed.birth_date, "10/01/2004");
  strcpy(parsed.address, "WA Seattle");

  printf("\nname: %s \nbirth_date: %s \naddress: %s", parsed.name, parsed.age, parsed.birth_date, parsed.address);

  // logic to parse file and return for whatever structure you need
  char input[BUF_SIZE];
  FILE *fptr = fopen("file.csv", "r");
  
  while((fget(input, BUF_SIZE, fptr)) != EOF) {
    
    for(size_t i=0; i<input.length(); i++) {
      
    }
  }


  fclose(fptr);
}


#endif
