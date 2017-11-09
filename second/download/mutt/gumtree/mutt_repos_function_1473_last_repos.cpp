void mutt_free_rx_list (RX_LIST **list)
{
  RX_LIST *p;
  
  if (!list) return;
  while (*list)
  {
    p = *list;
    *list = (*list)->next;
    mutt_free_regexp (&p->rx);
    FREE (&p);
  }
}