void mutt_free_list (LIST **list)
{
  LIST *p;
  
  if (!list) return;
  while (*list)
  {
    p = *list;
    *list = (*list)->next;
    safe_free ((void **) &p->data);
    safe_free ((void **) &p);
  }
}