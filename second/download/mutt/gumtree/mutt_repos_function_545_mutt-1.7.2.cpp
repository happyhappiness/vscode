void mx_alloc_memory (CONTEXT *ctx)
{
  int i;
  size_t s = MAX (sizeof (HEADER *), sizeof (int));
  
  if ((ctx->hdrmax + 25) * s < ctx->hdrmax * s)
  {
    mutt_error _("Integer overflow -- can't allocate memory.");
    sleep (1);
    mutt_exit (1);
  }
  
  if (ctx->hdrs)
  {
    safe_realloc (&ctx->hdrs, sizeof (HEADER *) * (ctx->hdrmax += 25));
    safe_realloc (&ctx->v2r, sizeof (int) * ctx->hdrmax);
  }
  else
  {
    ctx->hdrs = safe_calloc ((ctx->hdrmax += 25), sizeof (HEADER *));
    ctx->v2r = safe_calloc (ctx->hdrmax, sizeof (int));
  }
  for (i = ctx->msgcount ; i < ctx->hdrmax ; i++)
  {
    ctx->hdrs[i] = NULL;
    ctx->v2r[i] = -1;
  }
}