static int maildir_open_message (CONTEXT *ctx, MESSAGE *msg, int msgno)
{
  return maildir_mh_open_message (ctx, msg, msgno, 1);
}