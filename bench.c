#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"

double bench(size_t buffer_size, size_t niters) {
  struct timespec start, stop;
  size_t counter;
  data_t *buffer;
  size_t *offsets;
  double time, time_elapsed;
  volatile data_t _
      __attribute__((unused)); // volatile prevents dead code optimization,
                               // confirmed by checking the assembly. attribute
                               // unused prevents compiler warnings.

  time = 0;

  buffer = calloc(buffer_size, sizeof(data_t));
  offsets = calloc(10, sizeof(size_t));

  if (!buffer || !offsets) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(1);
  }

  for (counter = 0; counter < buffer_size; counter++) {
    buffer[counter] = rand();
  }

  for (counter = 0; counter < niters; counter++) {
    offsets[0] = rand() % buffer_size;
    offsets[1] = rand() % buffer_size;
    offsets[2] = rand() % buffer_size;
    offsets[3] = rand() % buffer_size;
    offsets[4] = rand() % buffer_size;
    offsets[5] = rand() % buffer_size;
    offsets[6] = rand() % buffer_size;
    offsets[7] = rand() % buffer_size;
    offsets[8] = rand() % buffer_size;
    offsets[9] = rand() % buffer_size;

    clock_gettime(CLOCK_MONOTONIC, &start);
    _ = buffer[offsets[0]];
    _ = buffer[offsets[1]];
    _ = buffer[offsets[2]];
    _ = buffer[offsets[3]];
    _ = buffer[offsets[4]];
    _ = buffer[offsets[5]];
    _ = buffer[offsets[6]];
    _ = buffer[offsets[7]];
    _ = buffer[offsets[8]];
    _ = buffer[offsets[9]];
    clock_gettime(CLOCK_MONOTONIC, &stop);

    time_elapsed =
        (stop.tv_sec - start.tv_sec) * 1e9 + (stop.tv_nsec - start.tv_nsec);
    time = time + time_elapsed / 10;
  }

  time = time / niters;

  free(buffer);
  free(offsets);

  return time;
}
