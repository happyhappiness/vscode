    FREE (&msg);

  return msg;
}

/* check for new mail */
int mx_check_mailbox (CONTEXT *ctx, int *index_hint)
{
  if (!ctx)
  {
    dprint (1, (debugfile, "mx_check_mailbox: null or invalid context.\n"));
    return -1;
  }

  return ctx->mx_ops->check (ctx, index_hint);
}

/* return a stream pointer for a message */
MESSAGE *mx_open_message (CONTEXT *ctx, int msgno)
{
  MESSAGE *msg;

  if (!ctx->mx_ops->open_msg)
  {
    dprint (1, (debugfile, "mx_open_message(): function not implemented for mailbox type %d.\n", ctx->magic));
    return NULL;
  }

  msg = safe_calloc (1, sizeof (MESSAGE));
  if (ctx->mx_ops->open_msg (ctx, msg, msgno))
    FREE (&msg);

  return msg;
}

/* commit a message to a folder */

int mx_commit_message (MESSAGE *msg, CONTEXT *ctx)
{
  if (!ctx->mx_ops->commit_msg)
    return -1;

  if (!(msg->write && ctx->append))
  {
    dprint (1, (debugfile, "mx_commit_message(): msg->write = %d, ctx->append = %d\n",
		msg->write, ctx->append));
    return -1;
  }

  return ctx->mx_ops->commit_msg (ctx, msg);
}

/* close a pointer to a message */
int mx_close_message (CONTEXT *ctx, MESSAGE **msg)
{
  int r = 0;

  if (ctx->mx_ops->close_msg)
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
