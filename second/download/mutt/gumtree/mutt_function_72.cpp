int mutt_write_mime_header (BODY *a, FILE *f)
{
  PARAMETER *p;
  char buffer[STRING];
  char *t;
  char *fn;
  int len;
  int tmplen;
  int encode;
  
  fprintf (f, "Content-Type: %s/%s", TYPE (a), a->subtype);

  if (a->parameter)
  {
    len = 25 + mutt_strlen (a->subtype); /* approximate len. of content-type */

    for(p = a->parameter; p; p = p->next)
    {
      char *tmp;
      
      if(!p->value)
	continue;
      
      fputc (';', f);

      buffer[0] = 0;
      tmp = safe_strdup (p->value);
      encode = rfc2231_encode_string (&tmp);
      rfc822_cat (buffer, sizeof (buffer), tmp, MimeSpecials);

      /* Dirty hack to make messages readable by Outlook Express 
       * for the Mac: force quotes around the boundary parameter
       * even when they aren't needed.
       */

      if (!ascii_strcasecmp (p->attribute, "boundary") && !strcmp (buffer, tmp))
	snprintf (buffer, sizeof (buffer), "\"%s\"", tmp);

      safe_free ((void **)&tmp);

      tmplen = mutt_strlen (buffer) + mutt_strlen (p->attribute) + 1;

      if (len + tmplen + 2 > 76)
      {
	fputs ("\n\t", f);
	len = tmplen + 8;
      }
      else
      {
	fputc (' ', f);
	len += tmplen + 1;
      }

      fprintf (f, "%s%s=%s", p->attribute, encode ? "*" : "", buffer);

    }
  }

  fputc ('\n', f);

  if (a->description)
    fprintf(f, "Content-Description: %s\n", a->description);

  fprintf (f, "Content-Disposition: %s", DISPOSITION (a->disposition));

  if (a->use_disp)
  {
    if(!(fn = a->d_filename))
      fn = a->filename;
    
    if (fn)
    {
      char *tmp;

      /* Strip off the leading path... */
      if ((t = strrchr (fn, '/')))
	t++;
      else
	t = fn;
      
      buffer[0] = 0;
      tmp = safe_strdup (t);
      encode = rfc2231_encode_string (&tmp);
      rfc822_cat (buffer, sizeof (buffer), tmp, MimeSpecials);
      safe_free ((void **)&tmp);
      fprintf (f, "; filename%s=%s", encode ? "*" : "", buffer);
    }
  }

  fputc ('\n', f);

  if (a->encoding != ENC7BIT)
    fprintf(f, "Content-Transfer-Encoding: %s\n", ENCODING (a->encoding));

  /* Do NOT add the terminator here!!! */
  return (ferror (f) ? -1 : 0);
}