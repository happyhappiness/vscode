static int mbox_close_mailbox (CONTEXT *ctx)
{
  if (ctx->append && ctx->fp)
  {
    mx_unlock_file (ctx->path, fileno (ctx->fp), 1);
    mutt_unblock_signals ();
  }

  safe_fclose (&ctx->fp);

  return 0;
}