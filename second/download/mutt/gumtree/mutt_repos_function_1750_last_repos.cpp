static int remove_from_replace_list (REPLACE_LIST **list, const char *pat)
{
  REPLACE_LIST *cur, *prev;
  int nremoved = 0;

  /* Being first is a special case. */
  cur = *list;
  if (!cur)
    return 0;
  if (cur->rx && !mutt_strcmp(cur->rx->pattern, pat))
  {
    *list = cur->next;
    mutt_free_regexp(&cur->rx);
    FREE(&cur->template);
    FREE(&cur);
    return 1;
  }

  prev = cur;
  for (cur = prev->next; cur;)
  {
    if (!mutt_strcmp(cur->rx->pattern, pat))
    {
      prev->next = cur->next;
      mutt_free_regexp(&cur->rx);
      FREE(&cur->template);
      FREE(&cur);
      cur = prev->next;
      ++nremoved;
    }
    else
      cur = cur->next;
  }

  return nremoved;
}