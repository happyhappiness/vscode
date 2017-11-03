int mx_close_message (CONTEXT *ctx, MESSAGE **msg)
{
  int r = 0;

  if (ctx->mx_ops && ctx->mx_ops->close_msg)
    r = ctx->mx_ops->close_msg (ctx, *msg);

  if ((*msg)->path)
  {
    dprint (1, (debugfile, "mx_close_message (): unlinking %s\n",
            (*msg)->path));
    unlink ((*msg)->path);
    FREE (&(*msg)->path);
  }

  FREE (msg);		/* __FREE_CHECKED__ */
  return (r);
}