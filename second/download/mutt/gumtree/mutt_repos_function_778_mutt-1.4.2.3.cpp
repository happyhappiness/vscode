void mutt_clear_threads (CONTEXT *ctx)
{
  int i;

  for (i = 0; i < ctx->msgcount; i++)
  {
    ctx->hdrs[i]->thread = NULL;
    ctx->hdrs[i]->threaded = 0;
  }
  ctx->tree = NULL;

  if (ctx->thread_hash)
    hash_destroy (&ctx->thread_hash, *free);
  if (ctx->subj_hash)
    hash_destroy (&ctx->subj_hash, NULL);
}