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
      mutt_error _("No boundary parameter found! [report this error]");
      return (-1);
    }
    strfcpy (boundary, p, sizeof (boundary));

    for (t = a->parts; t ; t = t->next)
    {
      fprintf (f, "\n--%s\n", boundary);
      if (mutt_write_mime_header (t, f) == -1)
	return -1;
      fputc ('\n', f);
      if (mutt_write_mime_body (t, f) == -1)
	return -1;
    }
    fprintf (f, "\n--%s--\n", boundary);
    return (ferror (f) ? -1 : 0);
  }

  /* This is pretty gross, but it's the best solution for now... */
  if ((WithCrypto & APPLICATION_PGP)
      && a->type == TYPEAPPLICATION
      && mutt_strcmp (a->subtype, "pgp-encrypted") == 0)
  {
    fputs ("Version: 1\n", f);
    return 0;
  }

  if ((fpin = fopen (a->filename, "r")) == NULL)
  {
    dprint(1,(debugfile, "write_mime_body: %s no longer exists!\n",a->filename));
    mutt_error (_("%s no longer exists!"), a->filename);
    return -1;
  }

  if (a->type == TYPETEXT && (!a->noconv))
    fc = fgetconv_open (fpin, a->charset,
			mutt_get_body_charset (send_charset, sizeof (send_charset), a),
			0);
  else
    fc = fgetconv_open (fpin, 0, 0, 0);

  if (a->encoding == ENCQUOTEDPRINTABLE)
    encode_quoted (fc, f, write_as_text_part (a));
  else if (a->encoding == ENCBASE64)
    encode_base64 (fc, f, write_as_text_part (a));
  else if (a->type == TYPETEXT && (!a->noconv))
    encode_8bit (fc, f, write_as_text_part (a));
  else
    mutt_copy_stream (fpin, f);

  fgetconv_close (&fc);
  safe_fclose (&fpin);

  return (ferror (f) ? -1 : 0);
}