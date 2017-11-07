static int include_forward (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  int chflags = CH_DECODE, cmflags = 0;
  
  mutt_parse_mime_message (ctx, cur);
  mutt_message_hook (ctx, cur, M_MESSAGEHOOK);

#ifdef HAVE_PGP
  if ((cur->pgp & PGPENCRYPT) && option (OPTFORWDECODE))
  {
    /* make sure we have the user's passphrase before proceeding... */
    pgp_valid_passphrase ();
  }
#endif /* HAVE_PGP */

  mutt_forward_intro (out, cur);

  if (option (OPTFORWDECODE))
  {
    cmflags |= M_CM_DECODE | M_CM_CHARCONV;
    if (option (OPTWEED))
    {
      chflags |= CH_WEED | CH_REORDER;
      cmflags |= M_CM_WEED;
    }
  }
  if (option (OPTFORWQUOTE))
    cmflags |= M_CM_PREFIX;

  mutt_copy_message (out, ctx, cur, cmflags, chflags);
  mutt_forward_trailer (out);
  return 0;
}