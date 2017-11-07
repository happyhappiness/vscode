static int mh_close_mailbox (CONTEXT *ctx)
{
  FREE (&ctx->data);

  return 0;
}