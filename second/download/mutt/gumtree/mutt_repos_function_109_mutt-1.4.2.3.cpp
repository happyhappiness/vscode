char *safe_strdup (const char *s)
{
  char *p;
  size_t l;

  if (!s || !*s)
    return 0;
  l = strlen (s) + 1;
  p = (char *)safe_malloc (l);
  memcpy (p, s, l);
  return (p);
}