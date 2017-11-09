void
mutt_free_compress_info (CONTEXT *ctx)
{
  COMPRESS_INFO *ci;

  if (!ctx || !ctx->compress_info)
    return;

  ci = ctx->compress_info;
  FREE (&ci->open);
  FREE (&ci->close);
  FREE (&ci->append);

  unlock_realpath (ctx);

  FREE (&ctx->compress_info);
}