
  if (!isnan(range->min) && (range->min > value))
    ret = 1;
  if (!isnan(range->max) && (range->max < value))
    ret = 1;

  return ((ret - range->invert) == 0) ? 0 : 1;
} /* int match_range */

__attribute__((noreturn)) static void usage(const char *name) {
  fprintf(stderr,
          "Usage: %s <-s socket> <-n value_spec> <-H hostname> [options]\n"
          "\n"
