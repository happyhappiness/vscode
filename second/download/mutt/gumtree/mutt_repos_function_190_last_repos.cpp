int mutt_strncmp(const char *a, const char *b, size_t l)
{
  return strncmp(NONULL(a), NONULL(b), l);
}