static HEADER *maildir_parse_message (int magic, const char *fname,
				      int is_old, HEADER * _h)
{
  FILE *f;
  HEADER *h = _h;
  struct stat st;

  if ((f = fopen (fname, "r")) != NULL)
  {
    if (!h)
      h = mutt_new_header ();
    h->env = mutt_read_rfc822_header (f, h, 0, 0);

    fstat (fileno (f), &st);
    safe_fclose (&f);

    if (!h->received)
      h->received = h->date_sent;

    /* always update the length since we have fresh information available. */
    h->content->length = st.st_size - h->content->offset;

    h->index = -1;

    if (magic == MUTT_MAILDIR)
    {
      /* 
       * maildir stores its flags in the filename, so ignore the
       * flags in the header of the message 
       */

      h->old = is_old;
      maildir_parse_flags (h, fname);
    }
    return h;
  }
  return NULL;
}