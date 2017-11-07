static const char *find_word (const char *src)
{
  const char *p = src;

  while (p && *p && strchr (" \t\n", *p))
    p++;
  while (p && *p && !strchr (" \t\n", *p))
    p++;
  return p;
}