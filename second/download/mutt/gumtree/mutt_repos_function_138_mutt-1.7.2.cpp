void mutt_pattern_free (pattern_t **pat)
{
  pattern_t *tmp;

  while (*pat)
  {
    tmp = *pat;
    *pat = (*pat)->next;

    if (tmp->stringmatch)
      FREE (&tmp->p.str);
    else if (tmp->groupmatch)
      tmp->p.g = NULL;
    else if (tmp->p.rx)
    {
      regfree (tmp->p.rx);
      FREE (&tmp->p.rx);
    }

    if (tmp->child)
      mutt_pattern_free (&tmp->child);
    FREE (&tmp);
  }
}