char *asubst(const char *string, int off1, int off2, const char *replacement) {
  char *buf;
  int len;

  char *ret;

  if ((NULL == string) || (0 > off1) || (0 > off2) || (off1 > off2) ||
      (NULL == replacement))
    return NULL;

  len = off1 + strlen(replacement) + strlen(string) - off2 + 1;

  buf = malloc(len);
  if (NULL == buf)
    return NULL;

  ret = subst(buf, len, string, off1, off2, replacement);
  if (NULL == ret)
    free(buf);
  return ret;
}