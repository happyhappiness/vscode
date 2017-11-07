static void pipe_msg (HEADER *h, FILE *fp, int decode, int print)
{
  int cmflags = 0;
  int chflags = CH_FROM;
  
  pipe_set_flags (decode, print, &cmflags, &chflags);

  if (WithCrypto && decode && h->security & ENCRYPT)
  {
    if(!crypt_valid_passphrase(h->security))
      return;
    endwin ();
  }

  if (decode)
    mutt_parse_mime_message (Context, h);

  mutt_copy_message (fp, Context, h, cmflags, chflags);
}