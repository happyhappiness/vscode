static char *
lt_estrdup (str)
     const char *str;
{
  char *copy = strdup (str);
  if (LT_STRLEN (str) && !copy)
    LT_DLMUTEX_SETERROR (LT_DLSTRERROR (NO_MEMORY));
  return copy;
}