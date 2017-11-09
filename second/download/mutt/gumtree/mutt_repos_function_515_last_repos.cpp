BODY *mutt_parse_multipart (FILE *fp, const char *boundary, LOFF_T end_off, int digest)
{
#ifdef SUN_ATTACHMENT
  int lines;
#endif
  int blen, len, crlf = 0;
  char buffer[LONG_STRING];
  BODY *head = 0, *last = 0, *new = 0;
  int i;
  int final = 0; /* did we see the ending boundary? */

  if (!boundary)
  {
    mutt_error _("multipart message has no boundary parameter!");
    return (NULL);
  }

  blen = mutt_strlen (boundary);
  while (ftello (fp) < end_off && fgets (buffer, LONG_STRING, fp) != NULL)
  {
    len = mutt_strlen (buffer);

    crlf =  (len > 1 && buffer[len - 2] == '\r') ? 1 : 0;

    if (buffer[0] == '-' && buffer[1] == '-' &&
	mutt_strncmp (buffer + 2, boundary, blen) == 0)
    {
      if (last)
      {
	last->length = ftello (fp) - last->offset - len - 1 - crlf;
	if (last->parts && last->parts->length == 0)
	  last->parts->length = ftello (fp) - last->parts->offset - len - 1 - crlf;
	/* if the body is empty, we can end up with a -1 length */
	if (last->length < 0)
	  last->length = 0;
      }

      /* Remove any trailing whitespace, up to the length of the boundary */
      for (i = len - 1; ISSPACE (buffer[i]) && i >= blen + 2; i--)
        buffer[i] = 0;

      /* Check for the end boundary */
      if (mutt_strcmp (buffer + blen + 2, "--") == 0)
      {
	final = 1;
	break; /* done parsing */
      }
      else if (buffer[2 + blen] == 0)
      {
	new = mutt_read_mime_header (fp, digest);

#ifdef SUN_ATTACHMENT
        if (mutt_get_parameter ("content-lines", new->parameter)) {
	  mutt_atoi (mutt_get_parameter ("content-lines", new->parameter), &lines);
	  for ( ; lines; lines-- )
	     if (ftello (fp) >= end_off || fgets (buffer, LONG_STRING, fp) == NULL)
	       break;
	}
#endif
	
	/*
	 * Consistency checking - catch
	 * bad attachment end boundaries
	 */
	
	if(new->offset > end_off)
	{
	  mutt_free_body(&new);
	  break;
	}
	if (head)
	{
	  last->next = new;
	  last = new;
	}
	else
	  last = head = new;
      }
    }
  }

  /* in case of missing end boundary, set the length to something reasonable */
  if (last && last->length == 0 && !final)
    last->length = end_off - last->offset;

  /* parse recursive MIME parts */
  for(last = head; last; last = last->next)
    mutt_parse_part(fp, last);
  
  return (head);
}