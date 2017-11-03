int mutt_group_context_remove_adrlist (group_context_t *ctx, ADDRESS * a)
{
  int rv = 0;

  for (; (!rv) && ctx; ctx = ctx->next)
  {
    rv = mutt_group_remove_adrlist (ctx->g, a);
    if (empty_group (ctx->g))
      mutt_group_remove (ctx->g);
  }

  return rv;
}