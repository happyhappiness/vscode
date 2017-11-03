void mutt_clear_threads (CONTEXT *ctx)
{
  int i;

  for (i = 0; i < ctx->msgcount; i++)
  {
    /* mailbox may have been only partially read */
    if (ctx->hdrs[i])
    {
      ctx->hdrs[i]->thread = NULL;
      ctx->hdrs[i]->threaded = 0;
    }
  }
  ctx->tree = NULL;

  if (ctx->thread_hash)
    hash_destroy (&ctx->thread_hash, *free);
}