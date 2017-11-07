void mx_fastclose_mailbox (CONTEXT *ctx)
{
  int i;

  if(!ctx) 
    return;

  /* never announce that a mailbox we've just left has new mail. #3290
   * XXX: really belongs in mx_close_mailbox, but this is a nice hook point */
  mutt_buffy_setnotified(ctx->path);

  if (ctx->mx_close)
    ctx->mx_close (ctx);

  if (ctx->subj_hash)
    hash_destroy (&ctx->subj_hash, NULL);
  if (ctx->id_hash)
    hash_destroy (&ctx->id_hash, NULL);
  mutt_clear_threads (ctx);
  for (i = 0; i < ctx->msgcount; i++)
    mutt_free_header (&ctx->hdrs[i]);
  FREE (&ctx->hdrs);
  FREE (&ctx->v2r);
  FREE (&ctx->path);
  FREE (&ctx->pattern);
  if (ctx->limit_pattern) 
    mutt_pattern_free (&ctx->limit_pattern);
  safe_fclose (&ctx->fp);
  memset (ctx, 0, sizeof (CONTEXT));
}