void mutt_free_spam_list (SPAM_LIST **list)
{
  SPAM_LIST *p;
  
  if (!list) return;
  while (*list)
  {
    p = *list;
    *list = (*list)->next;
    mutt_free_regexp (&p->rx);
    FREE (&p->template);
    FREE (&p);
  }
}