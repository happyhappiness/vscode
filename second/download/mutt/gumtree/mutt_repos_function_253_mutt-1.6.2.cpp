int mbox_close_mailbox (CONTEXT *ctx)
{
  mx_unlock_file (ctx->path, fileno (ctx->fp), 1);
  mutt_unblock_signals ();
  mx_fastclose_mailbox (ctx);
  return 0;
}