static int
close_message (CONTEXT *ctx, MESSAGE *msg)
{
  if (!ctx)
    return -1;

  COMPRESS_INFO *ci = ctx->compress_info;
  if (!ci)
    return -1;

  struct mx_ops *ops = ci->child_ops;
  if (!ops)
    return -1;

  /* Delegate */
  return ops->close_msg (ctx, msg);
}