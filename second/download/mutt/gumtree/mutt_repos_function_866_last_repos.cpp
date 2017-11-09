void mutt_label_hash_remove (CONTEXT *ctx, HEADER *hdr)
{
  if (!ctx || !ctx->label_hash)
    return;
  if (hdr->env->x_label)
    label_ref_dec (ctx, hdr->env->x_label);
}