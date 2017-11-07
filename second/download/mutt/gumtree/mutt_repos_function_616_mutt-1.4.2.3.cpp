static void attach_include_reply (FILE *fp, FILE *tmpfp, HEADER *cur, int flags)
{
  int cmflags = M_CM_PREFIX | M_CM_DECODE | M_CM_CHARCONV;
  int chflags = CH_DECODE;

  /* mutt_message_hook (cur, M_MESSAGEHOOK); */ 
  
  mutt_make_attribution (Context, cur, tmpfp);
  
  if (!option (OPTHEADER))
    cmflags |= M_CM_NOHEADER;
  if (option (OPTWEED))
  {
    chflags |= CH_WEED;
    cmflags |= M_CM_WEED;
  }

  _mutt_copy_message (tmpfp, fp, cur, cur->content, cmflags, chflags);
  mutt_make_post_indent (Context, cur, tmpfp);
}