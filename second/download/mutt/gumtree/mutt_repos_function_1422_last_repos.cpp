int mutt_remove_from_rx_list (RX_LIST **l, const char *str)
{
  RX_LIST *p, *last = NULL;
  int rv = -1;

  if (mutt_strcmp ("*", str) == 0)
  {
    mutt_free_rx_list (l);    /* ``unCMD *'' means delete all current entries */
    rv = 0;
  }
  else
  {
    p = *l;
    last = NULL;
    while (p)
    {
      if (ascii_strcasecmp (str, p->rx->pattern) == 0)
      {
	mutt_free_regexp (&p->rx);
	if (last)
	  last->next = p->next;
	else
	  (*l) = p->next;
	FREE (&p);
	rv = 0;
      }
      else
      {
	last = p;
	p = p->next;
      }
    }
  }
  return (rv);
}