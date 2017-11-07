int
mutt_copy_header (FILE *in, HEADER *h, FILE *out, int flags, const char *prefix)
{
  char buffer[SHORT_STRING];
  
  if (mutt_copy_hdr (in, out, h->offset, h->content->offset, flags, prefix) == -1)
    return (-1);

  if (flags & CH_TXTPLAIN)
  {
    char chsbuf[SHORT_STRING];
    fputs ("Mime-Version: 1.0\n", out);
    fputs ("Content-Transfer-Encoding: 8bit\n", out);
    fputs ("Content-Type: text/plain; charset=", out);
    mutt_canonical_charset (chsbuf, sizeof (chsbuf), Charset ? Charset : "us-ascii");
    rfc822_cat(buffer, sizeof(buffer), chsbuf, MimeSpecials);
    fputs(buffer, out);
    fputc('\n', out);
    
    if (ferror (out) != 0 || feof (out) != 0)
      return -1;
    
  }

  if (flags & CH_UPDATE)
  {
    if ((flags & CH_NOSTATUS) == 0)
    {
      if (h->old || h->read)
      {
	if (fputs ("Status: ", out) == EOF)
	  return (-1);

	if (h->read)
	{
	  if (fputs ("RO", out) == EOF)
	    return (-1);
	}
	else if (h->old)
	{
	  if (fputc ('O', out) == EOF)
	    return (-1);
	}

	if (fputc ('\n', out) == EOF)
	  return (-1);
      }

      if (h->flagged || h->replied)
      {
	if (fputs ("X-Status: ", out) == EOF)
	  return (-1);

	if (h->replied)
	{
	  if (fputc ('A', out) == EOF)
	    return (-1);
	}

	if (h->flagged)
	{
	  if (fputc ('F', out) == EOF)
	    return (-1);
	}
	
	if (fputc ('\n', out) == EOF)
	  return (-1);
      }
    }
  }

  if (flags & CH_UPDATE_LEN &&
      (flags & CH_NOLEN) == 0)
  {
    fprintf (out, "Content-Length: %ld\n", h->content->length);
    if (h->lines != 0 || h->content->length == 0)
      fprintf (out, "Lines: %d\n", h->lines);
  }

  if ((flags & CH_NONEWLINE) == 0)
  {
    if (flags & CH_PREFIX)
      fputs(prefix, out);
    if (fputc ('\n', out) == EOF) /* add header terminator */
      return (-1);
  }

  if (ferror (out) || feof (out))
    return -1;
  
  return (0);
}