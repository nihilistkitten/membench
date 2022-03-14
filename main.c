#include "bench.h"
#include <stdio.h>

#define NITERS 10000000
#define MAX_BUFFER 1 << 10
#define NSIZES 100

void bench_and_print(size_t buffer_size) {
  double mean_time = bench(buffer_size, NITERS);
  printf("%lu,%f\n", buffer_size / 1000, mean_time);
}

int main() {
  printf("Buffer Size (kb),Time (ns)\n");

  const int32_t diff = (MAX_BUFFER) / NSIZES;

  for (int32_t i = diff; i < MAX_BUFFER; i += diff) {
    bench_and_print(1000 * i);
  }

  return 0;
}
