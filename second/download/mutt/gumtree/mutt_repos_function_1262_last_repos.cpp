HASH *mutt_make_subj_hash (CONTEXT *ctx)
{
  int i;
  HEADER *hdr;
  HASH *hash;

  hash = hash_create (ctx->msgcount * 2, MUTT_HASH_ALLOW_DUPS);

  for (i = 0; i < ctx->msgcount; i++)
  {
    hdr = ctx->hdrs[i];
    if (hdr->env->real_subj)
      hash_insert (hash, hdr->env->real_subj, hdr);
  }

  return hash;
}