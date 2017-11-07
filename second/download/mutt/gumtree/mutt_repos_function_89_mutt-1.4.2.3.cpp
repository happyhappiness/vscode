void mutt_pattern_free (pattern_t **pat)
{
  pattern_t *tmp;

  while (*pat)
  {
    tmp = *pat;
    *pat = (*pat)->next;

    if (tmp->rx)
    {
      regfree (tmp->rx);
      safe_free ((void **) &tmp->rx);
    }
    if (tmp->child)
      mutt_pattern_free (&tmp->child);
    safe_free ((void **) &tmp);
  }
}