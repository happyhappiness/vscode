static char *unfold_header (char *s)
{
  char *p = s, *q = s;

  while (p && *p)
  {
    /* remove CRLF prior to FWSP, turn \t into ' ' */
    if (*p == '\r' && *(p + 1) && *(p + 1) == '\n' && *(p + 2) &&
	(*(p + 2) == ' ' || *(p + 2) == '\t'))
    {
      *q++ = ' ';
      p += 3;
      continue;
    }
    /* remove LF prior to FWSP, turn \t into ' ' */
    else if (*p == '\n' && *(p + 1) && (*(p + 1) == ' ' || *(p + 1) == '\t'))
    {
      *q++ = ' ';
      p += 2;
      continue;
    }
    *q++ = *p++;
  }
  if (q)
    *q = 0;

  return s;
}