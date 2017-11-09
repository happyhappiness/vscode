static int
parse_color_name (const char *s, int *col, int *attr, int is_fg, BUFFER *err)
{
  char *eptr;
  int is_bright = 0;

  if (ascii_strncasecmp (s, "bright", 6) == 0)
  {
    is_bright = 1;
    s += 6;
  }

  /* allow aliases for xterm color resources */
  if (ascii_strncasecmp (s, "color", 5) == 0)
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

  if (is_bright)
  {
    if (is_fg)
    {
      *attr |= A_BOLD;
    }
    else if (COLORS < 16)
    {
      /* A_BLINK turns the background color brite on some terms */
      *attr |= A_BLINK;
    }
    else
    {
      /* Advance the color by 8 to get the bright version */
      *col += 8;
    }
  }

  return 0;
}