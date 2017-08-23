int main(int argc, char* argv[])
{
  if (argc > 1) {
    printf("Usage: %s\n", argv[0]);
    return 1;
  }
  int res = 0;
#include "MathTestTests.h"
  if (res != 0) {
    printf("%s: %d math tests failed\n", argv[0], res);
    return 1;
  }
  return 0;
}