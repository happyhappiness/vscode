void pipe_msg (HEADER *h, FILE *fp, int decode, int print)
{
  int cmflags = 0;
  int chflags = CH_FROM;
  
  pipe_set_flags (decode, print, &cmflags, &chflags);

#ifdef HAVE_PGP
  
  if (decode && (h->pgp & PGPENCRYPT))
  {
    if (!pgp_valid_passphrase())
      return;
    endwin();
  }
  
#endif

  if (decode)
    mutt_parse_mime_message (Context, h);

  mutt_copy_message (fp, Context, h, cmflags, chflags);
}