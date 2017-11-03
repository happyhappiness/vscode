char *mutt_read_rfc822_line (FILE *f, char *line, size_t *linelen)
{
  char *buf = line;
  int ch;
  size_t offset = 0;
  size_t len = 0;

  FOREVER
  {
    if (fgets (buf, *linelen - offset, f) == NULL ||	/* end of file or */
	(ISSPACE (*line) && !offset))			/* end of headers */ 
    {
      *line = 0;
      return (line);
    }

    len = mutt_strlen (buf);
    if (! len)
      return (line);

    buf += len - 1;
    if (*buf == '\n')
    {
      /* we did get a full line. remove trailing space */
      while (ISSPACE (*buf))
	*buf-- = 0;	/* we cannot come beyond line's beginning because
			 * it begins with a non-space */

      /* check to see if the next line is a continuation line */
      if ((ch = fgetc (f)) != ' ' && ch != '\t')
      {
	ungetc (ch, f);
	return (line); /* next line is a separate header field or EOH */
      }

      /* eat tabs and spaces from the beginning of the continuation line */
      while ((ch = fgetc (f)) == ' ' || ch == '\t')
	;
      ungetc (ch, f);
      *++buf = ' '; /* string is still terminated because we removed
		       at least one whitespace char above */
    }

    buf++;
    offset = buf - line;
    if (*linelen < offset + STRING)
    {
      /* grow the buffer */
      *linelen += STRING;
      safe_realloc (&line, *linelen);
      buf = line + offset;
    }
  }
  /* not reached */
}