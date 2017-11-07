static void remove_from_list (LIST **l, const char *str)
{
  LIST *p, *last = NULL;

  if (mutt_strcmp ("*", str) == 0)
    mutt_free_list (l);    /* ``unCMD *'' means delete all current entries */
  else
  {
    p = *l;
    last = NULL;
    while (p)
    {
      if (ascii_strcasecmp (str, p->data) == 0)
      {
	FREE (&p->data);
	if (last)
	  last->next = p->next;
	else
	  (*l) = p->next;
	FREE (&p);
      }
      else
      {
	last = p;
	p = p->next;
      }
    }
  }
}