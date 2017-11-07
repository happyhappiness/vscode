char *mutt_substrdup (const char *begin, const char *end)
{
  size_t len;
  char *p;

  if (end)
    len = end - begin;
  else
    len = strlen (begin);

  p = safe_malloc (len + 1);
  memcpy (p, begin, len);
  p[len] = 0;
  return p;
}