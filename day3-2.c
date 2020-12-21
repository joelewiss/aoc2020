#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILENAME "day3.input"
#define BUF_SIZE 40


int main(void) {
  FILE *input_file;
  char line[BUF_SIZE];  /* Buffer for line */
  int trees[5] = {0};   /* Tree counters, one for each slope */
  short width;          /* Width of our given slope, calculated once */
  int x[5];             /* From the last problem, we really only need to keep
                           track of X. Do this in an array for each slope */
  int y;                /* Turns out we do need y, but only for the last case */
  int i;                /* Counter for some loops within the function */
  long result;          /* Stores the result of the multiplication of trees */

  input_file = fopen(FILENAME, "r");
  if (input_file != NULL) {

    /* Set initial coordinates */
    y = 1;
    for (i = 0; i < 5; i++)
      x[i] = 1;

    fgets(line, BUF_SIZE - 1, input_file); /* Leave space for terminating NUL */ 
    width = strlen(line) - 1; /* Subtract one to exclude newline */ 
    while (!feof(input_file)) {

      
      /* Check for trees on each slope */
      for (i = 0; i < 5; i++) {
        printf("%d: At %d,%d with character %c\n", i + 1, 
            x[i], y, line[x[i] - 1]);


        /* Sorta jank way for testing the last case, which is down 2 */
        if (i != 4) {
          if (line[x[i] - 1] == '#')
            trees[i]++;
        } else {
          /* Since we're starting at 1 and going down 2 every time, the rows
             we need to check are odd */
          if (y % 2 != 0) {
            if (line[x[i] - 1] == '#')
              trees[i]++;
          }
        }
      }


      /* Increment coordinates accordingly */
      /* Increment y always by one */
      y++;

      x[0] = (x[0] + 1) % width;
      x[1] = (x[1] + 3) % width;
      x[2] = (x[2] + 5) % width;
      x[3] = (x[3] + 7) % width;
      /* Only move last slope if we're on the correct y coordinate */
      if (y % 2 != 0) 
        x[4] = (x[4] + 1) % width;

      /* Check special case for all coordinates */
      /* Special case, if we've reached exactly the end of the line, x will be 0 */
      for (i = 0; i < 5; i++) {
        if (x[i] == 0)
          x[i] = width;
      }


      /* Get next line */
      fgets(line, BUF_SIZE - 1, input_file);
    }


    result = 1;
    puts("\n\n");
    for (i = 0; i < 5; i++) {
      printf("%d: Hit %d trees\n", i + 1, trees[i]);
      result *= trees[i];
    }


    printf("Product of tree counts: %ld\n", result);



  } else {
    puts("Could not open file " FILENAME " for reading.");
    return EXIT_FAILURE;
  }





  return EXIT_SUCCESS;
}
