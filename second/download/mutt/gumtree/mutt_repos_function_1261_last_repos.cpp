HASH *mutt_make_id_hash (CONTEXT *ctx)
{
  int i;
  HEADER *hdr;
  HASH *hash;

  hash = hash_create (ctx->msgcount * 2, 0);

  for (i = 0; i < ctx->msgcount; i++)
  {
    hdr = ctx->hdrs[i];
    if (hdr->env->message_id)
      hash_insert (hash, hdr->env->message_id, hdr);
  }

  return hash;
}