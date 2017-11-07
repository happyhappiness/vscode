void mutt_group_context_add_adrlist (group_context_t *ctx, ADDRESS *a)
{
  for (; ctx; ctx = ctx->next)
    mutt_group_add_adrlist (ctx->g, a);
}