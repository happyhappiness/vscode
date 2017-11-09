static int
check_mailbox (CONTEXT *ctx, int *index_hint)
{
  if (!ctx)
    return -1;

  COMPRESS_INFO *ci = ctx->compress_info;
  if (!ci)
    return -1;

  struct mx_ops *ops = ci->child_ops;
  if (!ops)
    return -1;

  int size = get_size (ctx->realpath);
  if (size == ci->size)
    return 0;

  if (!lock_realpath (ctx, 0))
  {
    mutt_error (_("Unable to lock mailbox!"));
    return -1;
  }

  int rc = execute_command (ctx, ci->open, _("Decompressing %s"));
  store_size (ctx);
  unlock_realpath (ctx);
  if (rc == 0)
    return -1;

  return ops->check (ctx, index_hint);
}