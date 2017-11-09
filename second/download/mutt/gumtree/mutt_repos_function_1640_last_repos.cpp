static int
open_new_message (MESSAGE *msg, CONTEXT *ctx, HEADER *hdr)
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
  return ops->open_new_msg (msg, ctx, hdr);
}