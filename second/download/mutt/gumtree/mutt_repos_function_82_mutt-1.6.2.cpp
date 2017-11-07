static int include_reply (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  int cmflags = M_CM_PREFIX | M_CM_DECODE | M_CM_CHARCONV | M_CM_REPLYING;
  int chflags = CH_DECODE;

  if (WithCrypto && (cur->security & ENCRYPT))
  {
    /* make sure we have the user's passphrase before proceeding... */
    crypt_valid_passphrase (cur->security);
  }

  mutt_parse_mime_message (ctx, cur);
  mutt_message_hook (ctx, cur, M_MESSAGEHOOK);
  
  mutt_make_attribution (ctx, cur, out);
  
  if (!option (OPTHEADER))
    cmflags |= M_CM_NOHEADER;
  if (option (OPTWEED))
  {
    chflags |= CH_WEED | CH_REORDER;
    cmflags |= M_CM_WEED;
  }

  mutt_copy_message (out, ctx, cur, cmflags, chflags);

  mutt_make_post_indent (ctx, cur, out);
  
  return 0;
}