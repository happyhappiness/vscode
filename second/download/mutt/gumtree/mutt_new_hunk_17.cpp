      ignore = 0;
    } /* If beginning of header */

    if (!ignore)
    {
      dprint (2, (debugfile, "Reorder: x = %d; hdr_count = %d\n", x, hdr_count));
      if (!this_one) {
	this_one = safe_strdup (buf);
	this_one_len = mutt_strlen (this_one);
      } else {
	int blen = mutt_strlen (buf);

	safe_realloc (&this_one, this_one_len + blen + sizeof (char));
	strcat (this_one + this_one_len, buf); /* __STRCAT_CHECKED__ */
	this_one_len += blen;
      }
    }
  } /* while (ftello (in) < off_end) */

  /* Do we have anything pending?  -- XXX, same code as in above in the loop. */
  if (this_one)
  {
    if (flags & CH_DECODE) 
    {
      if (!address_header_decode (&this_one))
	rfc2047_decode (&this_one);
    }
    
    if (!headers[x])
      headers[x] = this_one;
    else 
    {
      int hlen = mutt_strlen (headers[x]);

      safe_realloc (&headers[x], hlen + this_one_len + sizeof (char));
      strcat (headers[x] + hlen, this_one); /* __STRCAT_CHECKED__ */
      FREE (&this_one);
    }

    this_one = NULL;
  }

  /* Now output the headers in order */
  for (x = 0; x < hdr_count; x++)
  {
    if (headers[x])
    {
#if 0
      if (flags & CH_DECODE)
	rfc2047_decode (&headers[x]);
#endif

      /* We couldn't do the prefixing when reading because RFC 2047
       * decoding may have concatenated lines.
       */
      
      if (flags & (CH_DECODE|CH_PREFIX))
      {
	if (mutt_write_one_header (out, 0, headers[x], 
				   flags & CH_PREFIX ? prefix : 0, mutt_term_width (Wrap), flags) == -1)
	{
	  error = TRUE;
	  break;
	}
      }
      else
      {      
	if (fputs (headers[x], out) == EOF)
	{
	  error = TRUE;
