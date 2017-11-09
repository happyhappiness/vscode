static int mh_commit_message (CONTEXT * ctx, MESSAGE * msg)
{
  return _mh_commit_message (ctx, msg, NULL, 1);
}