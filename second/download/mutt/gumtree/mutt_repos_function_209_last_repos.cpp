void mutt_group_context_add (group_context_t **ctx, group_t *group)
{
  for (; *ctx; ctx = &((*ctx)->next))
  {
    if ((*ctx)->g == group)
      return;
  }

  *ctx = safe_calloc (1, sizeof (group_context_t));
  (*ctx)->g = group;
}