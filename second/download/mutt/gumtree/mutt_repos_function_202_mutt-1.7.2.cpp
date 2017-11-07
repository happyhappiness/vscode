int mutt_group_context_clear (group_context_t **ctx)
{
  group_context_t *t;
  for ( ; ctx && *ctx; (*ctx) = t)
  {
    mutt_group_remove ((*ctx)->g);
    t = (*ctx)->next;
    FREE(ctx);				/* __FREE_CHECKED__ */
  }
  return 0;
}