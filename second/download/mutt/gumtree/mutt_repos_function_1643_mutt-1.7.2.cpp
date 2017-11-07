int mutt_decode_save_attachment (FILE *fp, BODY *m, char *path,
				 int displaying, int flags)
{
  STATE s;
  unsigned int saved_encoding = 0;
  BODY *saved_parts = NULL;
  HEADER *saved_hdr = NULL;

  memset (&s, 0, sizeof (s));
  s.flags = displaying;

  if (flags == MUTT_SAVE_APPEND)
    s.fpout = fopen (path, "a");
  else if (flags == MUTT_SAVE_OVERWRITE)
    s.fpout = fopen (path, "w");	/* __FOPEN_CHECKED__ */
  else
    s.fpout = safe_fopen (path, "w");

  if (s.fpout == NULL)
  {
    mutt_perror ("fopen");
    return (-1);
  }

  if (fp == NULL)
  {
    /* When called from the compose menu, the attachment isn't parsed,
     * so we need to do it here. */
    struct stat st;

    if (stat (m->filename, &st) == -1)
    {
      mutt_perror ("stat");
      safe_fclose (&s.fpout);
      return (-1);
    }

    if ((s.fpin = fopen (m->filename, "r")) == NULL)
    {
      mutt_perror ("fopen");
      return (-1);
    }

    saved_encoding = m->encoding;
    if (!is_multipart (m))
      m->encoding = ENC8BIT;
    
    m->length = st.st_size;
    m->offset = 0;
    saved_parts = m->parts;
    saved_hdr = m->hdr;
    mutt_parse_part (s.fpin, m);

    if (m->noconv || is_multipart (m))
      s.flags |= MUTT_CHARCONV;
  }
  else
  {
    s.fpin = fp;
    s.flags |= MUTT_CHARCONV;
  }

  mutt_body_handler (m, &s);

  safe_fclose (&s.fpout);
  if (fp == NULL)
  {
    m->length = 0;
    m->encoding = saved_encoding;
    if (saved_parts)
    {
      mutt_free_header (&m->hdr);
      m->parts = saved_parts;
      m->hdr = saved_hdr;
    }
    safe_fclose (&s.fpin);
  }

  return (0);
}