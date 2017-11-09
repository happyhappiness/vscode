void mutt_free_color (int fg, int bg)
{
  COLOR_LIST *p, *q;

  p = ColorList;
  while (p)
  {
    if (p->fg == fg && p->bg == bg)
    {
      (p->count)--;
      if (p->count > 0) return;

      UserColors--;
      dprint(1,(debugfile,"mutt_free_color(): Color pairs used so far: %d\n",
                           UserColors));

      if (p == ColorList)
      {
	ColorList = ColorList->next;
	FREE (&p);
	return;
      }
      q = ColorList;
      while (q)
      {
	if (q->next == p)
	{
	  q->next = p->next;
	  FREE (&p);
	  return;
	}
	q = q->next;
      }
      /* can't get here */
    }
    p = p->next;
  }
}