static int include_forward (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  int chflags = CH_DECODE, cmflags = 0;
  
  mutt_parse_mime_message (ctx, cur);
  mutt_message_hook (ctx, cur, MUTT_MESSAGEHOOK);

  if (WithCrypto && (cur->security & ENCRYPT) && option (OPTFORWDECODE))
  {
    /* make sure we have the user's passphrase before proceeding... */
    crypt_valid_passphrase (cur->security);
  }

  mutt_forward_intro (ctx, cur, out);

  if (option (OPTFORWDECODE))
  {
    cmflags |= MUTT_CM_DECODE | MUTT_CM_CHARCONV;
    if (option (OPTWEED))
    {
      chflags |= CH_WEED | CH_REORDER;
      cmflags |= MUTT_CM_WEED;
    }
  }
  if (option (OPTFORWQUOTE))
    cmflags |= MUTT_CM_PREFIX;

  /* wrapping headers for forwarding is considered a display
   * rather than send action */
  chflags |= CH_DISPLAY;

  mutt_copy_message (out, ctx, cur, cmflags, chflags);
  mutt_forward_trailer (ctx, cur, out);
  return 0;
}