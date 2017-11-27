char *sstrdup(const char *s) {
  char *r;
  size_t sz;

  if (s == NULL)
    return NULL;

  /* Do not use `strdup' here, because it's not specified in POSIX. It's
   * ``only'' an XSI extension. */
  sz = strlen(s) + 1;
  r = malloc(sz);
  if (r == NULL) {
    ERROR("sstrdup: Out of memory.");
    exit(3);
  }
  memcpy(r, s, sz);

  return r;
}