#ifndef CSV_H
#define CSV_H

#define BUF_SIZE 256

// corresponds to each row of csv
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

#endif
