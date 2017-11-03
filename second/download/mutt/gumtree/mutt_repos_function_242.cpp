static int mbox_open_mailbox (CONTEXT *ctx)
{
  int rc;

  if ((ctx->fp = fopen (ctx->path, "r")) == NULL)
  {
    mutt_perror (ctx->path);
    return (-1);
  }
  mutt_block_signals ();
  if (mbox_lock_mailbox (ctx, 0, 1) == -1)
  {
    mutt_unblock_signals ();
    return (-1);
  }

  if (ctx->magic == MUTT_MBOX)
    rc = mbox_parse_mailbox (ctx);
  else if (ctx->magic == MUTT_MMDF)
    rc = mmdf_parse_mailbox (ctx);
  else
    rc = -1;

  mbox_unlock_mailbox (ctx);
  mutt_unblock_signals ();
  return (rc);
}