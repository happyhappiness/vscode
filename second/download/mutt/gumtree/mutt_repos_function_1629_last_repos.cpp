static char *
escape_path (char *src)
{
  static char dest[HUGE_STRING];
  char *destp = dest;
  int destsize = 0;

  if (!src)
    return NULL;

  while (*src && (destsize < sizeof(dest) - 1))
  {
    if (*src != '\'')
    {
      *destp++ = *src++;
      destsize++;
    }
    else
    {
      /* convert ' into '\'' */
      if (destsize + 4 < sizeof(dest))
      {
        *destp++ = *src++;
        *destp++ = '\\';
        *destp++ = '\'';
        *destp++ = '\'';
        destsize += 4;
      }
      else
        break;
    }
  }
  *destp = '\0';

  return dest;
}