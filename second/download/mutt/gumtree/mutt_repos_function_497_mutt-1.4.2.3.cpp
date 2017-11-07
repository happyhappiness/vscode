static int
parse_color_name (const char *s, int *col, int *attr, int brite, BUFFER *err)
{
  char *eptr;

  if (mutt_strncasecmp (s, "bright", 6) == 0)
  {
    *attr |= brite;
    s += 6;
  }

  /* allow aliases for xterm color resources */
  if (mutt_strncasecmp (s, "color", 5) == 0)
  {
    s += 5;
    *col = strtol (s, &eptr, 10);
    if (!*s || *eptr || *col < 0 ||
	(*col >= COLORS && !option(OPTNOCURSES) && has_colors()))
    {
      snprintf (err->data, err->dsize, _("%s: color not supported by term"), s);
      return (-1);
    }
  }
  else if ((*col = mutt_getvaluebyname (s, Colors)) == -1)
  {
    snprintf (err->data, err->dsize, _("%s: no such color"), s);
    return (-1);
  }

  return 0;
}