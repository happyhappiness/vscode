void mutt_free_replace_list (REPLACE_LIST **list)
{
  REPLACE_LIST *p;
  
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