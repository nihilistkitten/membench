#include "bench.h"
#include <stdio.h>

#define NITERS 1e7
#define MAX_BUFFER 1 << 30
#define NSIZES 100

#define BYTE_TO_KB 1000

void bench_and_print(size_t buffer_size) {
  double mean_time = bench(buffer_size, NITERS);
  printf("%f,%f\n", (double)buffer_size / BYTE_TO_KB, mean_time);
}

int main() {
  printf("Buffer Size (kb),Mean Latency per Read (ns)\n");

  const int32_t diff = (MAX_BUFFER) / NSIZES;

  srand(0);
  for (int32_t i = diff; i < MAX_BUFFER; i += diff) {
    bench_and_print(i);
  }

  return 0;
}
