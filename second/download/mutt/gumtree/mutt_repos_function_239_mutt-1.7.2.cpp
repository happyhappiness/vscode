void mbox_unlock_mailbox (CONTEXT *ctx)
{
  if (ctx->locked)
  {
    fflush (ctx->fp);

    mx_unlock_file (ctx->path, fileno (ctx->fp), 1);
    ctx->locked = 0;
  }
}