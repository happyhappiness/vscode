static int
lock_realpath (CONTEXT *ctx, int excl)
{
  if (!ctx)
    return 0;

  COMPRESS_INFO *ci = ctx->compress_info;
  if (!ci)
    return 0;

  if (ci->locked)
    return 1;

  if (excl)
    ci->lockfp = fopen (ctx->realpath, "a");
  else
    ci->lockfp = fopen (ctx->realpath, "r");
  if (!ci->lockfp)
  {
    mutt_perror (ctx->realpath);
    return 0;
  }

  int r = mx_lock_file (ctx->realpath, fileno (ci->lockfp), excl, 1, 1);

  if (r == 0)
    ci->locked = 1;
  else if (excl == 0)
  {
    safe_fclose (&ci->lockfp);
    ctx->readonly = 1;
    return 1;
  }

  return (r == 0);
}