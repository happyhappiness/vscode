void mutt_group_context_destroy (group_context_t **ctx)
{
  group_context_t *p;
  for (; *ctx; *ctx = p)
  {
    p = (*ctx)->next;
    FREE (ctx);		/* __FREE_CHECKED__ */
  }
}