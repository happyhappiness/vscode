static void
unlock_realpath (CONTEXT *ctx)
{
  if (!ctx)
    return;

  COMPRESS_INFO *ci = ctx->compress_info;
  if (!ci)
    return;

  if (!ci->locked)
    return;

  mx_unlock_file (ctx->realpath, fileno (ci->lockfp), 1);

  ci->locked = 0;
  safe_fclose (&ci->lockfp);
}