void mutt_make_label_hash (CONTEXT *ctx)
{
  /* 131 is just a rough prime estimate of how many distinct
   * labels someone might have in a mailbox.
   */
  ctx->label_hash = hash_create(131, MUTT_HASH_STRDUP_KEYS);
}