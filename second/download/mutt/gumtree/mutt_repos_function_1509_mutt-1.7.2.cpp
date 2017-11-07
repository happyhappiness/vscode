static int maildir_open_mailbox (CONTEXT *ctx)
{
  return maildir_read_dir (ctx);
}