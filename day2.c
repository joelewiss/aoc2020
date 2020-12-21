#include <stdio.h>
#include <stdlib.h>
#define FILENAME "day2.input"
#define LINE_SIZE 50


int main(void) {
  FILE *input_file;
  char pass[50];      /* Buffer for password */
  char *curr;         /* Pointer for incrementing through list */
  int a, b;           /* Low bound, high bound */
  int valid;          /* Number of valid passwords */
  int count;          /* Specific count of character for current line */
  char c;             /* Constraint character */

  input_file = fopen(FILENAME, "r");
  if (input_file != NULL) {
    valid = 0;

    while (!feof(input_file)) {
      if (fscanf(input_file, "%d-%d %c: ", &a, &b, &c) == 3) {
        fscanf(input_file, "%s", pass);
        
        curr = pass;
        count = 0;
        do {
          if (*curr == c)
            count++;

        } while (*++curr != '\0');

        if (count >= a && count <= b)
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
