int eat_range (pattern_t *pat, BUFFER *s, BUFFER *err)
{
  char *tmp;
  int do_exclusive = 0;
  int skip_quote = 0;
  
  /*
   * If simple_search is set to "~m %s", the range will have double quotes 
   * around it...
   */
  if (*s->dptr == '"')
  {
    s->dptr++;
    skip_quote = 1;
  }
  if (*s->dptr == '<')
    do_exclusive = 1;
  if ((*s->dptr != '-') && (*s->dptr != '<'))
  {
    /* range minimum */
    if (*s->dptr == '>')
    {
      pat->max = MUTT_MAXRANGE;
      pat->min = strtol (s->dptr + 1, &tmp, 0) + 1; /* exclusive range */
    }
    else
      pat->min = strtol (s->dptr, &tmp, 0);
    if (toupper ((unsigned char) *tmp) == 'K') /* is there a prefix? */
    {
      pat->min *= 1024;
      tmp++;
    }
    else if (toupper ((unsigned char) *tmp) == 'M')
    {
      pat->min *= 1048576;
      tmp++;
    }
    if (*s->dptr == '>')
    {
      s->dptr = tmp;
      return 0;
    }
    if (*tmp != '-')
    {
      /* exact value */
      pat->max = pat->min;
      s->dptr = tmp;
      return 0;
    }
    tmp++;
  }
  else
  {
    s->dptr++;
    tmp = s->dptr;
  }
  
  if (isdigit ((unsigned char) *tmp))
  {
    /* range maximum */
    pat->max = strtol (tmp, &tmp, 0);
    if (toupper ((unsigned char) *tmp) == 'K')
    {
      pat->max *= 1024;
      tmp++;
    }
    else if (toupper ((unsigned char) *tmp) == 'M')
    {
      pat->max *= 1048576;
      tmp++;
    }
    if (do_exclusive)
      (pat->max)--;
  }
  else
    pat->max = MUTT_MAXRANGE;

  if (skip_quote && *tmp == '"')
    tmp++;

  SKIPWS (tmp);
  s->dptr = tmp;
  return 0;
}