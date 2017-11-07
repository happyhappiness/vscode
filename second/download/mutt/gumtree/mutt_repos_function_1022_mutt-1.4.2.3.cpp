static HEADER *maildir_parse_message(int magic, const char *fname, int is_old)
{
  FILE *f;
  HEADER *h = NULL;
  struct stat st;
  
  if ((f = fopen (fname, "r")) != NULL)
  {
    h = mutt_new_header();
    h->env = mutt_read_rfc822_header (f, h, 0, 0);

    fstat (fileno (f), &st);
    fclose (f);

    if (!h->received)
      h->received = h->date_sent;

    if (h->content->length <= 0)
      h->content->length = st.st_size - h->content->offset;

    h->index = -1;

    if (magic == M_MAILDIR)
    {
      /* maildir stores its flags in the filename, so ignore the flags in
       * the header of the message
       */

      h->old = is_old;
      maildir_parse_flags(h, fname);
    }
  }
  return h;
}