static int sync_mailbox (CONTEXT *ctx, int *index_hint)
{
  if (!ctx->mx_ops || !ctx->mx_ops->sync)
    return -1;

  if (!ctx->quiet)
    mutt_message (_("Writing %s..."), ctx->path);

  return ctx->mx_ops->sync (ctx, index_hint);
}