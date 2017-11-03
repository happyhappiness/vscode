static int mbox_open_message (CONTEXT *ctx,  MESSAGE *msg, int msgno)
{
  msg->fp = ctx->fp;

  return 0;
}