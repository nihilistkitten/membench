#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"

#define ITERS 10000000
#define BUFFER_SIZE 10000000

int main() {
  struct timespec start, stop;
  double time_elapsed, mean_time;
  size_t counter, offset;
  data_t *buffer;
  double *times;
  volatile data_t x
      __attribute__((unused)); // volatile prevents dead code optimization,
                               // confirmed by checking the assembly. attribute
                               // unused prevents compiler warnings.

  buffer = calloc(BUFFER_SIZE, sizeof(data_t));
  times = calloc(ITERS, sizeof(double));

  if (!buffer || !times) {
    fprintf(stderr, "Memory allocation failed!\n");
    return 1;
  }

  srand(0);
  for (counter = 0; counter < BUFFER_SIZE; counter++) {
    buffer[counter] = rand();
  }

  for (counter = 0; counter < ITERS; counter++) {
    offset = rand() % BUFFER_SIZE;

    clock_gettime(CLOCK_MONOTONIC, &start);
    x = buffer[offset];
    clock_gettime(CLOCK_MONOTONIC, &stop);

    time_elapsed =
        (stop.tv_sec - start.tv_sec) * 1e9 + (stop.tv_nsec - start.tv_nsec);
    times[counter] = time_elapsed;
  }

  mean_time = 0;
  for (counter = 0; counter < ITERS; counter++) {
    mean_time += times[counter];
  }
  mean_time = mean_time / ITERS;

  printf("Mean time: %fns\n", mean_time);

  free(buffer);
  free(times);
}
