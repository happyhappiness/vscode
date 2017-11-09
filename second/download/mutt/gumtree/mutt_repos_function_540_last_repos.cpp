void mx_fastclose_mailbox (CONTEXT *ctx)
{
  int i;
  struct utimbuf ut;

  if(!ctx) 
    return;

  /* fix up the times so buffy won't get confused */
  if (ctx->peekonly && ctx->path && (ctx->mtime > ctx->atime)) {
    ut.actime  = ctx->atime;
    ut.modtime = ctx->mtime;
    utime (ctx->path, &ut);
  }

  /* never announce that a mailbox we've just left has new mail. #3290
   * XXX: really belongs in mx_close_mailbox, but this is a nice hook point */
  if (!ctx->peekonly)
    mutt_buffy_setnotified(ctx->path);

  if (ctx->mx_ops)
    ctx->mx_ops->close (ctx);

#ifdef USE_COMPRESSED
  mutt_free_compress_info (ctx);
#endif /* USE_COMPRESSED */

  if (ctx->subj_hash)
    hash_destroy (&ctx->subj_hash, NULL);
  if (ctx->id_hash)
    hash_destroy (&ctx->id_hash, NULL);
  hash_destroy (&ctx->label_hash, NULL);
  mutt_clear_threads (ctx);
  for (i = 0; i < ctx->msgcount; i++)
    mutt_free_header (&ctx->hdrs[i]);
  FREE (&ctx->hdrs);
  FREE (&ctx->v2r);
  FREE (&ctx->path);
  FREE (&ctx->realpath);
  FREE (&ctx->pattern);
  if (ctx->limit_pattern) 
    mutt_pattern_free (&ctx->limit_pattern);
  safe_fclose (&ctx->fp);
  memset (ctx, 0, sizeof (CONTEXT));
}