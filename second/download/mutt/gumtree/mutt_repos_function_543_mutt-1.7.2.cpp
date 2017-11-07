int mx_commit_message (MESSAGE *msg, CONTEXT *ctx)
{
  if (!ctx->mx_ops || !ctx->mx_ops->commit_msg)
    return -1;

  if (!(msg->write && ctx->append))
  {
    dprint (1, (debugfile, "mx_commit_message(): msg->write = %d, ctx->append = %d\n",
		msg->write, ctx->append));
    return -1;
  }

  return ctx->mx_ops->commit_msg (ctx, msg);
}