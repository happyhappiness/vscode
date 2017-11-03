int mutt_strcasecmp(const char *a, const char *b)
{
  return strcasecmp(NONULL(a), NONULL(b));
}