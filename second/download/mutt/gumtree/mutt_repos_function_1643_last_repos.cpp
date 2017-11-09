static int
sync_mailbox (CONTEXT *ctx, int *index_hint)
{
  if (!ctx)
    return -1;

  COMPRESS_INFO *ci = ctx->compress_info;
  if (!ci)
    return -1;

  if (!ci->close)
  {
    mutt_error (_("Can't sync a compressed file without a close-hook"));
    return -1;
  }

  struct mx_ops *ops = ci->child_ops;
  if (!ops)
    return -1;

  if (!lock_realpath (ctx, 1))
  {
    mutt_error (_("Unable to lock mailbox!"));
    return -1;
  }

  int rc = check_mailbox (ctx, index_hint);
  if (rc != 0)
    goto sync_cleanup;

  rc = ops->sync (ctx, index_hint);
  if (rc != 0)
    goto sync_cleanup;

  rc = execute_command (ctx, ci->close, _("Compressing %s"));
  if (rc == 0)
  {
    rc = -1;
    goto sync_cleanup;
  }

  rc = 0;

sync_cleanup:
  store_size (ctx);
  unlock_realpath (ctx);
  return rc;
}