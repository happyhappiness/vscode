int mx_check_mailbox (CONTEXT *ctx, int *index_hint)
{
  if (!ctx || !ctx->mx_ops)
  {
    dprint (1, (debugfile, "mx_check_mailbox: null or invalid context.\n"));
    return -1;
  }

  return ctx->mx_ops->check (ctx, index_hint);
}