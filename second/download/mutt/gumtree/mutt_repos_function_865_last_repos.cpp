void mutt_label_hash_add (CONTEXT *ctx, HEADER *hdr)
{
  if (!ctx || !ctx->label_hash)
    return;
  if (hdr->env->x_label)
    label_ref_inc (ctx, hdr->env->x_label);
}