int mutt_group_context_remove_rx (group_context_t *ctx, const char *s)
{
  int rv = 0;

  for (; (!rv) && ctx; ctx = ctx->next)
  {
    rv = mutt_group_remove_rx (ctx->g, s);
    if (empty_group (ctx->g))
      mutt_group_remove (ctx->g);
  }

  return rv;
}