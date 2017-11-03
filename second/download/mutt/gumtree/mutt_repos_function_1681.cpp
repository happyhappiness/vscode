static int
parse_sort (short *val, const char *s, const struct mapping_t *map, BUFFER *err)
{
  int i, flags = 0;

  if (mutt_strncmp ("reverse-", s, 8) == 0)
  {
    s += 8;
    flags = SORT_REVERSE;
  }
  
  if (mutt_strncmp ("last-", s, 5) == 0)
  {
    s += 5;
    flags |= SORT_LAST;
  }

  if ((i = mutt_getvaluebyname (s, map)) == -1)
  {
    snprintf (err->data, err->dsize, _("%s: unknown sorting method"), s);
    return (-1);
  }

  *val = i | flags;

  return 0;
}