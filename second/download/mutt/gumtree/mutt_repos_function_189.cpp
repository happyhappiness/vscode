const char *mutt_stristr (const char *haystack, const char *needle)
{
  const char *p, *q;

  if (!haystack)
    return NULL;
  if (!needle)
    return (haystack);

  while (*(p = haystack))
  {
    for (q = needle;
         *p && *q &&
           tolower ((unsigned char) *p) == tolower ((unsigned char) *q);
         p++, q++)
      ;
    if (!*q)
      return (haystack);
    haystack++;
  }
  return NULL;
}