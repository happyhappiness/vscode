static int strtouint64(const char *s, uint64_t *n) {
  char *endptr = NULL;

  assert(s != NULL);
  assert(n != NULL);

  *n = strtoull(s, &endptr, 0);

  if (!(*s != '\0' && *endptr == '\0')) {
    DEBUG(RDT_PLUGIN ": Error converting '%s' to unsigned number.", s);
    return -EINVAL;
  }

  return 0;
}