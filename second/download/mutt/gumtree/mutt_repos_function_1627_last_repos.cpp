static COMPRESS_INFO *
set_compress_info (CONTEXT *ctx)
{
  if (!ctx || !ctx->path)
    return NULL;

  if (ctx->compress_info)
    return ctx->compress_info;

  /* Open is compulsory */
  const char *o = find_hook (MUTT_OPENHOOK,   ctx->path);
  if (!o)
    return NULL;

  const char *c = find_hook (MUTT_CLOSEHOOK,  ctx->path);
  const char *a = find_hook (MUTT_APPENDHOOK, ctx->path);

  COMPRESS_INFO *ci = safe_calloc (1, sizeof (COMPRESS_INFO));
  ctx->compress_info = ci;

  ci->open   = safe_strdup (o);
  ci->close  = safe_strdup (c);
  ci->append = safe_strdup (a);

  return ci;
}