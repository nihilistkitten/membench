#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"

double bench(size_t buffer_size, size_t niters) {
  struct timespec start, stop;
  double time_elapsed, mean_time;
  size_t counter, offset;
  data_t *buffer;
  double *times;
  volatile data_t _
      __attribute__((unused)); // volatile prevents dead code optimization,
                               // confirmed by checking the assembly. attribute
                               // unused prevents compiler warnings.

  buffer = calloc(buffer_size, sizeof(data_t));
  times = calloc(niters, sizeof(double));

  if (!buffer || !times) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(1);
  }

  for (counter = 0; counter < buffer_size; counter++) {
    buffer[counter] = rand();
  }

  for (counter = 0; counter < niters; counter++) {
    offset = rand() % buffer_size;

    clock_gettime(CLOCK_MONOTONIC, &start);
    _ = buffer[offset];
    clock_gettime(CLOCK_MONOTONIC, &stop);

    time_elapsed =
        (stop.tv_sec - start.tv_sec) * 1e9 + (stop.tv_nsec - start.tv_nsec);
    times[counter] = time_elapsed;
  }

  mean_time = 0;
  for (counter = 0; counter < niters; counter++) {
    mean_time += times[counter];
  }
  mean_time = mean_time / niters;

  free(buffer);
  free(times);

  return mean_time;
}
