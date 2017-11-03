static int mbox_close_message (CONTEXT *ctx, MESSAGE *msg)
{
  msg->fp = NULL;

  return 0;
}