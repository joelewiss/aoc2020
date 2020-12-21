#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILENAME        "day4.input"
#define BUF_SIZE        100
#define SMALL_BUF_SIZE  20
#define FIELDS          7


static char *fields[FIELDS] = {"byr",
                               "iyr",
                               "eyr",
                               "hgt",
                               "hcl",
                               "ecl",
                               "pid"};
typedef struct {
  int byr;
  int iyr;
  int eyr;
  char *hgt;
  char *hcl;
  char *ecl;
  char *pid;
  int count;
} Passport;


int check_fields(Passport *p);


int main(void) {
  FILE *input_file;
  char line[BUF_SIZE];        /* Buffer for line */
  char *pos;                  /* Temporary pointer for storing position on
                                 line */
  static Passport p;          /* Passport for storing values */
  int valid, i;               /* Total valid and loop counters */


  input_file = fopen(FILENAME, "r");
  if (input_file != NULL) {
    valid = 0;
    p.count = 0;

    fgets(line, BUF_SIZE - 1, input_file); /* Leave space for terminating
                                              NUL */ 
    while (!feof(input_file)) {

      /* If this isn't a passport seperator, look for fields */
      if (strcmp(line, "\n") != 0) {
        for (i = 0; i < FIELDS; i++) {
          pos = strstr(line, fields[i]);

          if (pos != NULL) {
            switch (i) {
              case 0:
                /* byr */ 
                sscanf(pos, "byr:%d", &p.byr);
                break;

              case 1:
                /* iyr */
                sscanf(pos, "iyr:%d", &p.iyr);
                break;

              case 2:
                /* eyr */
                sscanf(pos, "eyr:%d", &p.eyr);
                break;

              case 3:
                /* hgt */
                p.hgt = malloc(6); /* hgt field will be at max 5 chars, plus 
                                      one for NUL */
                sscanf(pos, "hgt:%s", p.hgt);
                break;

              case 4:
                /* hcl */
                p.hcl = malloc(8);
                sscanf(pos, "hcl:#%s", p.hcl);
                break;

              case 5:
                /* ecl */
                p.ecl = malloc(4);
                sscanf(pos, "ecl:%s", p.ecl);
                break;

              case 6:
                /* pid */
                p.pid = malloc(10);
                sscanf(pos, "pid:%s", p.pid);
                break;
            }

            p.count++;
          }
        }
      } else {
        if (check_fields(&p))
          valid++;

        p.count = 0;
      }


      fgets(line, BUF_SIZE - 1, input_file); /* Leave space for terminating
                                                NUL */
    }

    /* This code will miss the last passport entry, since the input dosen't
       end with a single newline */
    if (check_fields(&p))
      valid++;


    printf("Found %d valid passports\n", valid);


  } else {
    puts("Could not open file " FILENAME " for reading.");
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}



int check_fields(Passport *p) {
  int valid = 1;
  char c[SMALL_BUF_SIZE];   /* Some placeholder fields for comparisons */
  int i;


  if (p -> count >= 7) {
    /* Check byr */
    if (p -> byr < 1920 || p -> byr > 2002)
      valid = 0;

    /* Check iyr */
    if (p -> iyr < 2010 || p -> iyr > 2020)
      valid = 0;

    /* Check eyr */
    if (p -> eyr < 2020 || p -> eyr > 2030)
      valid = 0;

    /* Check hgt */
    if (sscanf(p -> hgt, "%d%s", &i, c) == 2) {
      if (strcmp(c, "cm") == 0) {
        /* cm check */
        if (i < 150 || i > 193)
          valid = 0;

      } else if (strcmp(c, "in") == 0) {
        /* in check */
        if (i < 59 || i > 76)
          valid = 0;
      } else {
        valid = 0;
      }
    } else {
      valid = 0;
    }


    /* Check hcl */
    if(sscanf(p -> hcl, "%[0-9a-f]", c) != 1)
      valid = 0;
    if(strcmp(c, p -> hcl) != 0)
      valid = 0;


    /* Check ecl */
    if (strlen(p -> ecl) == 3) {
      if (strcmp(p -> ecl, "amb") != 0 &&
          strcmp(p -> ecl, "blu") != 0 &&
          strcmp(p -> ecl, "brn") != 0 &&
          strcmp(p -> ecl, "gry") != 0 &&
          strcmp(p -> ecl, "grn") != 0 &&
          strcmp(p -> ecl, "hzl") != 0 &&
          strcmp(p -> ecl, "oth") != 0)
        valid = 0;
    } else {
      valid = 0;
    }


    /* Check pid */
    if (strlen(p -> pid) != 9)
      valid = 0;

  } else {
    valid = 0;
  }


  return valid;
}
