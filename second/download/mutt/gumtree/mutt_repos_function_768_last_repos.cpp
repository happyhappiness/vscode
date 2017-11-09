static char *list_to_pattern (LIST *list)
{
  LIST *l;
  char *pattern, *p;
  const char *s;
  size_t n;

  n = 0;
  for(l=list; l; l = l->next)
    {
      for(s = l->data; *s; s++)
        {
          if (*s == '%' || *s == '+')
            n += 2;
          n++;
        }
      n++; /* delimiter or end of string */
    }
  n++; /* make sure to allocate at least one byte */
  pattern = p = safe_calloc (1,n);
  for(l=list; l; l = l->next)
    {
      s = l->data;
      if (*s)
        {
          if (l != list)
            *p++ = ' ';
          for(s = l->data; *s; s++)
            {
              if (*s == '%')
                {
                  *p++ = '%';
                  *p++ = '2';
                  *p++ = '5';
                }
              else if (*s == '+')
                {
                  *p++ = '%';
                  *p++ = '2';
                  *p++ = 'B';
                }
              else if (*s == ' ')
                *p++ = '+';
              else
                *p++ = *s;
            }
        }
    }
  *p = 0;
  return pattern;
}