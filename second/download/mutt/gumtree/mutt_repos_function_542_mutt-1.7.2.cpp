MESSAGE *mx_open_message (CONTEXT *ctx, int msgno)
{
  MESSAGE *msg;

  if (!ctx->mx_ops || !ctx->mx_ops->open_msg)
  {
    dprint (1, (debugfile, "mx_open_message(): function not implemented for mailbox type %d.\n", ctx->magic));
    return NULL;
  }

  msg = safe_calloc (1, sizeof (MESSAGE));
  if (ctx->mx_ops->open_msg (ctx, msg, msgno))
    FREE (&msg);

  return msg;
}