char *mutt_read_line (char *s, size_t *size, FILE *fp, int *line, int flags)
{
  size_t offset = 0;
  char *ch;

  if (!s)
  {
    s = safe_malloc (STRING);
    *size = STRING;
  }

  FOREVER
  {
    if (fgets (s + offset, *size - offset, fp) == NULL)
    {
      FREE (&s);
      return NULL;
    }
    if ((ch = strchr (s + offset, '\n')) != NULL)
    {
      if (line)
	(*line)++;
      if (flags & MUTT_EOL)
	return s;
      *ch = 0;
      if (ch > s && *(ch - 1) == '\r')
	*--ch = 0;
      if (!(flags & MUTT_CONT) || ch == s || *(ch - 1) != '\\')
	return s;
      offset = ch - s - 1;
    }
    else
    {
      int c;
      c = getc (fp); /* This is kind of a hack. We want to know if the
                        char at the current point in the input stream is EOF.
                        feof() will only tell us if we've already hit EOF, not
                        if the next character is EOF. So, we need to read in
                        the next character and manually check if it is EOF. */
      if (c == EOF)
      {
        /* The last line of fp isn't \n terminated */
	if (line)
	  (*line)++;
        return s;
      }
      else
      {
        ungetc (c, fp); /* undo our damage */
        /* There wasn't room for the line -- increase ``s'' */
        offset = *size - 1; /* overwrite the terminating 0 */
        *size += STRING;
        safe_realloc (&s, *size);
      }
    }
  }
}