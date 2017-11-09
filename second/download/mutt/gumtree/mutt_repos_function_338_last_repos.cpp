int ascii_strcasecmp (const char *a, const char *b)
{
  int i;
  
  if (a == b)
    return 0;
  if (a == NULL && b)
    return -1;
  if (b == NULL && a)
    return 1;
  
  for (;; a++, b++)
  {
    if ((i = ascii_tolower (*a) - ascii_tolower (*b)))
      return i;
    /* test for NUL here rather that in the for loop in order to detect unqual
     * length strings (see http://dev.mutt.org/trac/ticket/3601)
     */
    if (!*a)
      break;
  }
  
  return 0;
}