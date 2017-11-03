static int remove_from_spam_list (SPAM_LIST **list, const char *pat)
{
  SPAM_LIST *spam, *prev;
  int nremoved = 0;

  /* Being first is a special case. */
  spam = *list;
  if (!spam)
    return 0;
  if (spam->rx && !mutt_strcmp(spam->rx->pattern, pat))
  {
    *list = spam->next;
    mutt_free_regexp(&spam->rx);
    FREE(&spam->template);
    FREE(&spam);
    return 1;
  }

  prev = spam;
  for (spam = prev->next; spam;)
  {
    if (!mutt_strcmp(spam->rx->pattern, pat))
    {
      prev->next = spam->next;
      mutt_free_regexp(&spam->rx);
      FREE(&spam->template);
      FREE(&spam);
      spam = prev->next;
      ++nremoved;
    }
    else
      spam = spam->next;
  }

  return nremoved;
}