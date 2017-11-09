static int label_message(CONTEXT *ctx, HEADER *hdr, char *new)
{
  if (hdr == NULL)
    return 0;
  if (mutt_strcmp (hdr->env->x_label, new) == 0)
    return 0;

  if (hdr->env->x_label != NULL)
    label_ref_dec(ctx, hdr->env->x_label);
  mutt_str_replace (&hdr->env->x_label, new);
  if (hdr->env->x_label != NULL)
    label_ref_inc(ctx, hdr->env->x_label);

  return hdr->changed = hdr->xlabel_changed = 1;
}