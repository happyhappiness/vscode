char *safe_strcat (char *d, size_t l, const char *s)
{
  char *p = d;

  if (!l) 
    return d;

  l--; /* Space for the trailing '\0'. */
  
  for (; *d && l; l--)
    d++;
  for (; *s && l; l--)
    *d++ = *s++;

  *d = '\0';
  
  return p;
}