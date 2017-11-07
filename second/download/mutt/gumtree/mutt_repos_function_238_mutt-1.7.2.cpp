int mbox_lock_mailbox (CONTEXT *ctx, int excl, int retry)
{
  int r;

  if ((r = mx_lock_file (ctx->path, fileno (ctx->fp), excl, 1, retry)) == 0)
    ctx->locked = 1;
  else if (retry && !excl)
  {
    ctx->readonly = 1;
    return 0;
  }
  
  return (r);
}