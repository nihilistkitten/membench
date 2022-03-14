#include "bench.h"
#include <stdio.h>

#define NITERS 1000000

void bench_and_print(size_t buffer_size) {
  double mean_time = bench(buffer_size, NITERS);
  printf("%lu, %f\n", buffer_size / 1000, mean_time);
}

int main() {
  printf("Buffer Size (kb), Time (ns)\n");

  for (int16_t i = 0; i < 20; i++) {
    // start at 1kb
    bench_and_print(1000 << i);
  }

  return 0;
}
