static int include_reply (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  int cmflags = M_CM_PREFIX | M_CM_DECODE | M_CM_CHARCONV;
  int chflags = CH_DECODE;

#ifdef HAVE_PGP
  if (cur->pgp)
  {
    if (cur->pgp & PGPENCRYPT)
    {
      /* make sure we have the user's passphrase before proceeding... */
      pgp_valid_passphrase ();
    }
  }
#endif /* HAVE_PGP */

  mutt_parse_mime_message (ctx, cur);
  mutt_message_hook (ctx, cur, M_MESSAGEHOOK);
  
  mutt_make_attribution (ctx, cur, out);
  
  if (!option (OPTHEADER))
    cmflags |= M_CM_NOHEADER;
  if (option (OPTWEED))
  {
    chflags |= CH_WEED;
    cmflags |= M_CM_WEED;
  }

  mutt_copy_message (out, ctx, cur, cmflags, chflags);

  mutt_make_post_indent (ctx, cur, out);
  
  return 0;
}