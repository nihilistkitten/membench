#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"

#define ITERS 1000000
#define BUFFER_SIZE 100
#define FETCHES_PER_ITER 1

int main(int argc, char *argv[]) {
  struct timespec start, stop;
  double time_elapsed, mean_time;
  size_t counter, offset_counter;
  data_t *buffer;
  size_t *offsets;
  double *times;
  volatile data_t x
      __attribute__((unused)); // volatile prevents dead code optimization,
                               // confirmed by checking the assembly. attribute
                               // unused prevents compiler warnings.

  buffer = calloc(BUFFER_SIZE, sizeof(data_t));
  offsets = calloc(FETCHES_PER_ITER, sizeof(size_t));
  times = calloc(ITERS, sizeof(double));

  if (!buffer || !offsets || !times) {
    fprintf(stderr, "Memory allocation failed!\n");
    return 1;
  }

  srand(0);
  for (counter = 0; counter < BUFFER_SIZE; counter++) {
    buffer[counter] = rand();
  }

  for (counter = 0; counter < ITERS; counter++) {
    for (offset_counter = 0; offset_counter < FETCHES_PER_ITER;
         offset_counter++) {
      // generate randoms outside of timing loop
      offsets[offset_counter] = rand() % BUFFER_SIZE;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (offset_counter = 0; offset_counter < FETCHES_PER_ITER;
         offset_counter++) {
      x = buffer[offsets[offset_counter]];
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);

    time_elapsed =
        (stop.tv_sec - start.tv_sec) * 1e9 + (stop.tv_nsec - start.tv_nsec);
    times[counter] = time_elapsed;
  }

  mean_time = 0;
  for (counter = 0; counter < ITERS; counter++) {
    printf("Iteration %zu: %fns\n", counter, times[counter] / FETCHES_PER_ITER);
    mean_time += times[counter];
  }
  mean_time = mean_time / (ITERS * FETCHES_PER_ITER);

  printf("Mean time: %fns\n", mean_time);

  free(buffer);
  free(offsets);
  free(times);
}
