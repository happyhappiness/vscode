BODY *mutt_read_mime_header (FILE *fp, int digest)
{
  BODY *p = mutt_new_body();
  char *c;
  char *line = safe_malloc (LONG_STRING);
  size_t linelen = LONG_STRING;
  
  p->hdr_offset  = ftell(fp);

  p->encoding    = ENC7BIT; /* default from RFC1521 */
  p->type        = digest ? TYPEMESSAGE : TYPETEXT;
  p->disposition = DISPINLINE;
  
  while (*(line = read_rfc822_line (fp, line, &linelen)) != 0)
  {
    /* Find the value of the current header */
    if ((c = strchr (line, ':')))
    {
      *c = 0;
      c++;
      SKIPWS (c);
      if (!*c)
      {
	dprint (1, (debugfile, "mutt_read_mime_header(): skipping empty header field: %s\n", line));
	continue;
      }
    }
    else
    {
      dprint (1, (debugfile, "read_mime_header: bogus MIME header: %s\n", line));
      break;
    }

    if (!ascii_strncasecmp ("content-", line, 8))
    {
      if (!ascii_strcasecmp ("type", line + 8))
	mutt_parse_content_type (c, p);
      else if (!ascii_strcasecmp ("transfer-encoding", line + 8))
	p->encoding = mutt_check_encoding (c);
      else if (!ascii_strcasecmp ("disposition", line + 8))
	parse_content_disposition (c, p);
      else if (!ascii_strcasecmp ("description", line + 8))
      {
	mutt_str_replace (&p->description, c);
	rfc2047_decode (&p->description);
      }
    } 
#ifdef SUN_ATTACHMENT
    else if (!ascii_strncasecmp ("x-sun-", line, 6))
    {
      if (!ascii_strcasecmp ("data-type", line + 6))
        mutt_parse_content_type (c, p);
      else if (!ascii_strcasecmp ("encoding-info", line + 6))
        p->encoding = mutt_check_encoding (c);
      else if (!ascii_strcasecmp ("content-lines", line + 6))
        mutt_set_parameter ("content-lines", safe_strdup (c), &(p->parameter));
      else if (!ascii_strcasecmp ("data-description", line + 6))
      {
	mutt_str_replace (&p->description, c);
        rfc2047_decode (&p->description);
      }
    }
#endif
  }
  p->offset = ftell (fp); /* Mark the start of the real data */
  if (p->type == TYPETEXT && !p->subtype)
    p->subtype = safe_strdup ("plain");
  else if (p->type == TYPEMESSAGE && !p->subtype)
    p->subtype = safe_strdup ("rfc822");

  FREE (&line);

  return (p);
}