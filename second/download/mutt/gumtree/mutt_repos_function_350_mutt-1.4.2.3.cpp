void mx_alloc_memory (CONTEXT *ctx)
{
  int i;

  if (ctx->hdrs)
  {
    safe_realloc ((void **) &ctx->hdrs, sizeof (HEADER *) * (ctx->hdrmax += 25));
    safe_realloc ((void **) &ctx->v2r, sizeof (int) * ctx->hdrmax);
  }
  else
  {
    ctx->hdrs = safe_malloc (sizeof (HEADER *) * (ctx->hdrmax += 25));
    ctx->v2r = safe_malloc (sizeof (int) * ctx->hdrmax);
  }
  for (i = ctx->msgcount ; i < ctx->hdrmax ; i++)
  {
    ctx->hdrs[i] = NULL;
    ctx->v2r[i] = -1;
  }
}