
  fputc ('\n', f);

  if (a->description)
    fprintf(f, "Content-Description: %s\n", a->description);

  if (a->disposition != DISPNONE)
  {
    const char *dispstr[] = {
      "inline",
      "attachment",
      "form-data"
    };

    if (a->disposition < sizeof(dispstr)/sizeof(char*))
    {
      fprintf (f, "Content-Disposition: %s", dispstr[a->disposition]);

      if (a->use_disp)
      {
	if (!(fn = a->d_filename))
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
	  FREE (&tmp);
	  fprintf (f, "; filename%s=%s", encode ? "*" : "", buffer);
	}
      }

      fputc ('\n', f);
    }
    else
    {
      dprint(1, (debugfile, "ERROR: invalid content-disposition %d\n", a->disposition));
    }
  }

  if (a->encoding != ENC7BIT)
    fprintf(f, "Content-Transfer-Encoding: %s\n", ENCODING (a->encoding));

  /* Do NOT add the terminator here!!! */
  return (ferror (f) ? -1 : 0);
}

# define write_as_text_part(a)  (mutt_is_text_part(a) \
                                 || ((WithCrypto & APPLICATION_PGP)\
                                      && mutt_is_application_pgp(a)))

int mutt_write_mime_body (BODY *a, FILE *f)
{
  char *p, boundary[SHORT_STRING];
  char send_charset[SHORT_STRING];
  FILE *fpin;
  BODY *t;
  FGETCONV *fc;

  if (a->type == TYPEMULTIPART)
  {
    /* First, find the boundary to use */
    if (!(p = mutt_get_parameter ("boundary", a->parameter)))
    {
      dprint (1, (debugfile, "mutt_write_mime_body(): no boundary parameter found!\n"));
