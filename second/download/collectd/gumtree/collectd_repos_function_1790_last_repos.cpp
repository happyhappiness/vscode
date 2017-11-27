uint64_t strtoull_safe(const char *str, int *err) {
  uint64_t val = 0;
  char *endptr;
  int res = 0;

  val = strtoull(str, &endptr, 16);
  if (*endptr) {
    ERROR("%s Failed to parse the value %s, endptr=%c", __FUNCTION__, str,
          *endptr);
    res = -EINVAL;
  }
  if (err != NULL)
    *err = res;
  return val;
}