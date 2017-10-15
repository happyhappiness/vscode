      ignore = 0;
    } /* If beginning of header */

    if (!ignore)
    {
      dprint (2, (debugfile, "Reorder: x = %d; hdr_count = %d\n", x, hdr_count));
      /* Save the header in headers[x] */
      if (!headers[x])
	headers[x] = safe_strdup (buf);
      else
      {
	safe_realloc ((void **) &headers[x],
		      mutt_strlen (headers[x]) + mutt_strlen (buf) + sizeof (char));
	strcat (headers[x], buf);	/* __STRCAT_CHECKED__ */
      }
    }
  } /* while (ftell (in) < off_end) */

  /* Now output the headers in order */
  for (x = 0; x < hdr_count; x++)
  {
    if (headers[x])
    {
      if (flags & CH_DECODE)
	rfc2047_decode (&headers[x]);

      /* We couldn't do the prefixing when reading because RFC 2047
       * decoding may have concatenated lines.
       */
      if (flags & CH_PREFIX)
      {
	char *ch = headers[x];
	int print_prefix = 1;

	while (*ch)
	{ 
	  if (print_prefix)
	  {
	    if (fputs (prefix, out) == EOF)
	    {
	      error = TRUE;
	      break;
	    }
	    print_prefix = 0;
	  }

	  if (*ch == '\n' && ch[1])
	    print_prefix = 1;

	  if (putc (*ch++, out) == EOF)
	  {
	    error = TRUE;
	    break;
	  }
	}
	if (error)
	  break;
      }
      else
      {      
	if (fputs (headers[x], out) == EOF)
	{
	  error = TRUE;
