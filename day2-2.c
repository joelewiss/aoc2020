#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILENAME "day2.input"
#define LINE_SIZE 50


int main(void) {
  FILE *input_file;
  char pass[50];      /* Buffer for password */
  int a, b;           /* Low bound, high bound */
  int valid;          /* Number of valid passwords */
  char c;             /* Constraint character */

  input_file = fopen(FILENAME, "r");
  if (input_file != NULL) {
    valid = 0;

    while (!feof(input_file)) {
      if (fscanf(input_file, "%d-%d %c: ", &a, &b, &c) == 3) {
        fscanf(input_file, "%s", pass);
       
        /* Although this is a bitwise exclusive OR, it should still work for our purposes */
        if ((pass[a - 1] == c) ^ (pass[b - 1] == c))
          valid++;


      } else {
        /* If we dont find the format we're expecting, print an error */
        /* Its also possible we reached the end of the file, if this is true,
           the EOF flag should now be set */
        if (!feof(input_file))
          puts("Invalid line encountered");
      }
    }

    printf("Found %d valid passwords\n", valid);

  } else {
    puts("Could not open file " FILENAME " for reading.");
    return EXIT_FAILURE;
  }





  return EXIT_SUCCESS;
}
