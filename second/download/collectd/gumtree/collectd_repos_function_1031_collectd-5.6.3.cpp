static int match_range(range_t *range, double value) {
  int ret = 0;

  if (!isnan(range->min) && (range->min > value))
    ret = 1;
  if (!isnan(range->max) && (range->max < value))
    ret = 1;

  return (((ret - range->invert) == 0) ? 0 : 1);
}