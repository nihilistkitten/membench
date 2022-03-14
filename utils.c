#include "types.h"
#include <stdlib.h>

/// Fetch a single piece of data from an array.
void fetch_from(size_t offset, data_t *array) {
  volatile data_t _ = array[offset];
}
