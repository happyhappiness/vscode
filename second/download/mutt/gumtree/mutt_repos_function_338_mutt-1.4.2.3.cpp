void mx_fastclose_mailbox (CONTEXT *ctx)
{
  int i;

  if(!ctx) 
    return;
  
#ifdef USE_IMAP
  if (ctx->magic == M_IMAP)
    imap_close_mailbox (ctx);
#endif /* USE_IMAP */
#ifdef USE_POP
  if (ctx->magic == M_POP)
    pop_close_mailbox (ctx);
#endif /* USE_POP */
  if (ctx->id_hash)
    hash_destroy (&ctx->id_hash, NULL);
  mutt_clear_threads (ctx);
  for (i = 0; i < ctx->msgcount; i++)
    mutt_free_header (&ctx->hdrs[i]);
  safe_free ((void **) &ctx->hdrs);
  safe_free ((void **) &ctx->v2r);
  safe_free ((void **) &ctx->path);
  safe_free ((void **) &ctx->pattern);
  if (ctx->limit_pattern) 
    mutt_pattern_free (&ctx->limit_pattern);
  safe_fclose (&ctx->fp);
  memset (ctx, 0, sizeof (CONTEXT));
}