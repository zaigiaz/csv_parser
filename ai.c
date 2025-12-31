// parser.c
#ifndef PARSER_H
#define PARSER_H

#define SEPERATOR ','
#define ENDL '\n'

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUF_SIZE 256

// define for debugging
#define PARSER_MAIN

// structure of information being parsed
struct info {
  char name[BUF_SIZE];
  char birth_date[BUF_SIZE];
  char address[BUF_SIZE];
};

/* Parse a CSV line into fields array. Returns number of fields parsed.
   Handles quoted fields that may contain separators. */
static int parse_csv_line(const char *line, char fields[][BUF_SIZE], int max_fields) {
  int field_idx = 0;
  const char *p = line;

  while(*p != '\0' && *p != '\r' && *p != '\n') {
    if(field_idx >= max_fields) break;
    char buf[BUF_SIZE] = {0};
    size_t bi = 0;

    if(*p == '"') {
      p++; /* skip initial quote */
      while(*p != '\0') {
        if(*p == '"') {
          if(*(p+1) == '"') { /* escaped quote "" -> " */
            if(bi + 1 < BUF_SIZE-1) buf[bi++] = '"';
            p += 2;
            continue;
          } else { /* end quote */
            p++;
            break;
          }
        } else {
          if(bi + 1 < BUF_SIZE-1) buf[bi++] = *p;
          p++;
        }
      }
      /* after closing quote, skip to separator or end */
      while(*p != '\0' && *p != SEPERATOR && *p != '\r' && *p != '\n') p++;
      if(*p == SEPERATOR) p++;
    } else {
      /* unquoted field */
      while(*p != '\0' && *p != SEPERATOR && *p != '\r' && *p != '\n') {
        if(bi + 1 < BUF_SIZE-1) buf[bi++] = *p;
        p++;
      }
      if(*p == SEPERATOR) p++;
    }

    buf[bi] = '\0';
    /* trim whitespace */
    char *start = buf;
    while(isspace((unsigned char)*start)) start++;
    char *end = start + strlen(start) - 1;
    while(end >= start && isspace((unsigned char)*end)) { *end = '\0'; end--; }

    strncpy(fields[field_idx], start, BUF_SIZE-1);
    fields[field_idx][BUF_SIZE-1] = '\0';
    field_idx++;
  }

  return field_idx;
}

void parse_file(void) {
  struct info parsed;
  char line[BUF_SIZE];

  FILE *fptr = fopen("file.csv", "r");
  if(!fptr) {
    perror("fopen");
    return;
  }

  /* Optionally skip header line if file has one */
  if(fgets(line, sizeof(line), fptr) == NULL) {
    fclose(fptr);
    return;
  }

  /* If the first line is a header, uncomment next line to skip it */
  // ; // already read header and discarded

  /* Process remaining lines */
  while(fgets(line, sizeof(line), fptr) != NULL) {
    char fields[3][BUF_SIZE] = {{0},{0},{0}};
    int n = parse_csv_line(line, fields, 3);

    /* Make reasonable defaults if fields missing */
    strncpy(parsed.name, (n > 0 ? fields[0] : ""), BUF_SIZE-1);
    parsed.name[BUF_SIZE-1] = '\0';
    strncpy(parsed.birth_date, (n > 1 ? fields[1] : ""), BUF_SIZE-1);
    parsed.birth_date[BUF_SIZE-1] = '\0';
    strncpy(parsed.address, (n > 2 ? fields[2] : ""), BUF_SIZE-1);
    parsed.address[BUF_SIZE-1] = '\0';

    printf("name: %s\nbirth_date: %s\naddress: %s\n\n",
           parsed.name, parsed.birth_date, parsed.address);
  }

  fclose(fptr);
}

/* Simple main to demo */
#ifdef PARSER_MAIN
int main(void) {
  parse_file();
  return 0;
}
#endif

#endif
