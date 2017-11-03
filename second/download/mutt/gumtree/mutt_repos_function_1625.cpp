void index_make_entry (char *s, size_t l, MUTTMENU *menu, int num)
{
  format_flag flag = MUTT_FORMAT_MAKEPRINT | MUTT_FORMAT_ARROWCURSOR | MUTT_FORMAT_INDEX;
  int edgemsgno, reverse = Sort & SORT_REVERSE;
  HEADER *h = Context->hdrs[Context->v2r[num]];
  THREAD *tmp;

  if ((Sort & SORT_MASK) == SORT_THREADS && h->tree)
  {
    flag |= MUTT_FORMAT_TREE; /* display the thread tree */
    if (h->display_subject)
      flag |= MUTT_FORMAT_FORCESUBJ;
    else
    {
      if (reverse)
      {
	if (menu->top + menu->pagelen > menu->max)
	  edgemsgno = Context->v2r[menu->max - 1];
	else
	  edgemsgno = Context->v2r[menu->top + menu->pagelen - 1];
      }
      else
	edgemsgno = Context->v2r[menu->top];

      for (tmp = h->thread->parent; tmp; tmp = tmp->parent)
      {
	if (!tmp->message)
	  continue;

	/* if no ancestor is visible on current screen, provisionally force
	 * subject... */
	if (reverse ? tmp->message->msgno > edgemsgno : tmp->message->msgno < edgemsgno)
	{
	  flag |= MUTT_FORMAT_FORCESUBJ;
	  break;
	}
	else if (tmp->message->virtual >= 0)
	  break;
      }
      if (flag & MUTT_FORMAT_FORCESUBJ)
      {
	for (tmp = h->thread->prev; tmp; tmp = tmp->prev)
	{
	  if (!tmp->message)
	    continue;

	  /* ...but if a previous sibling is available, don't force it */
	  if (reverse ? tmp->message->msgno > edgemsgno : tmp->message->msgno < edgemsgno)
	    break;
	  else if (tmp->message->virtual >= 0)
	  {
	    flag &= ~MUTT_FORMAT_FORCESUBJ;
	    break;
	  }
	}
      }
    }
  }

  _mutt_make_string (s, l, NONULL (HdrFmt), Context, h, flag);
}