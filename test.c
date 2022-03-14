#include <stdbool.h>
#include <stdio.h>

void assert_test(bool result, char name[], char message[]) {
  if (!result) {
    printf("Test %s failed: %s", name, message);
  }
}

int main(int argc, char *argv[]) { assert_test(false, "test1", "a != b"); }
