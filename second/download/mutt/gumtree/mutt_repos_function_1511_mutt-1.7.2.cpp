static int mh_open_mailbox (CONTEXT *ctx)
{
  return mh_read_dir (ctx, NULL);
}