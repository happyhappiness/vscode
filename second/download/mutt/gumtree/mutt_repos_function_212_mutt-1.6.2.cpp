int mutt_group_context_add_rx (group_context_t *ctx, const char *s, int flags, BUFFER *err)
{
  int rv = 0;

  for (; (!rv) && ctx; ctx = ctx->next)
    rv = mutt_group_add_rx (ctx->g, s, flags, err);

  return rv;
}