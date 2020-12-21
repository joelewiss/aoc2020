#include <stdio.h>
#include <stdlib.h>
#define FILENAME "day1.input"
#define INPUT_NUM 200


int main(void) {
  static int nums[INPUT_NUM];
  FILE *input_file;
  int i, j, k;

  input_file = fopen(FILENAME, "r");
  if (input_file != NULL) {
    for (i = 0; i < INPUT_NUM; i++) {
      fscanf(input_file, "%d\n", &nums[i]);
    }

    if (!feof(input_file)) {
      fprintf(stderr, "Seems there was more than %d lines", INPUT_NUM);
      return EXIT_FAILURE;
    } 

    for (i = 0; i < INPUT_NUM; i++) {
      for (j = 0; j < INPUT_NUM; j++) {
        for (k = 0; k < INPUT_NUM; k++) {

          if (nums[i] + nums[j] + nums[k] == 2020) {
            printf("Found numbers at index %d, %d, and %d\n", i, j, k);
            printf("Numbers multiplied is %d\n", nums[i] * nums[j] * nums[k]);
            /* Escape both loops by setting counters to INPUT_NUM */
            k = j = i = INPUT_NUM;
          }
        }
      }
    }

  }





  return EXIT_SUCCESS;
}
