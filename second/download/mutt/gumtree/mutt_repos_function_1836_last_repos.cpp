void mutt_sb_set_buffystats (const CONTEXT *ctx)
{
  /* Even if the sidebar's hidden,
   * we should take note of the new data. */
  BUFFY *b = Incoming;
  if (!ctx || !b)
    return;

  for (; b; b = b->next)
  {
    if (!mutt_strcmp (b->realpath, ctx->realpath))
    {
      b->msg_unread  = ctx->unread;
      b->msg_count   = ctx->msgcount;
      b->msg_flagged = ctx->flagged;
      break;
    }
  }
}