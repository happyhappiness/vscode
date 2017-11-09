static void
store_size (const CONTEXT *ctx)
{
  if (!ctx)
    return;

  COMPRESS_INFO *ci = ctx->compress_info;
  if (!ci)
    return;

  ci->size = get_size (ctx->realpath);
}