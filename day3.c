#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILENAME "day3.input"
#define BUF_SIZE 50


int main(void) {
  FILE *input_file;
  char line[BUF_SIZE];  /* Buffer for line */
  int trees;            /* Tree counter */
  short width;          /* Width of our given slope, calculated once */
  int x, y;             /* X, Y Coordinates on the slope starting from 1, 1 in
                           the top left */

  input_file = fopen(FILENAME, "r");
  if (input_file != NULL) {
    trees = 0;

    /* Start at odd coordinates, so our first check is at 1, 1 */
    x = -2;
    y = 0;

    fgets(line, BUF_SIZE - 1, input_file); /* Leave space for terminating NUL */ 
    width = strlen(line) - 1; /* Subtract one to exclude newline */ 
    while (!feof(input_file)) {
      x = (x + 3) % width;
      y += 1;

      /* Special case, if we've reached exactly the end of the line, x will be 0 */
      if (x == 0)
        x = width;

      printf("At coordinates %d,%d with character %c\n", x, y, line[x - 1]);

      /* Subtract one to get correct index */
      if (line[x - 1] == '#')
        trees++;


      fgets(line, BUF_SIZE - 1, input_file);
    }


    printf("\n\nHit %d trees\n", trees);


  } else {
    puts("Could not open file " FILENAME " for reading.");
    return EXIT_FAILURE;
  }





  return EXIT_SUCCESS;
}
