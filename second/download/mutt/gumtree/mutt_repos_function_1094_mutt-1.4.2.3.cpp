static void update_index (MUTTMENU *menu, CONTEXT *ctx, int check,
			  int oldcount, int index_hint)
{
  /* store pointers to the newly added messages */
  HEADER  **save_new = NULL;
  int j;
  
  /* take note of the current message */
  if (oldcount)
  {
    if (menu->current < Context->vcount)
      menu->oldcurrent = index_hint;
    else
      oldcount = 0; /* invalid message number! */
  }
  
  /* We are in a limited view. Check if the new message(s) satisfy
   * the limit criteria. If they do, set their virtual msgno so that
   * they will be visible in the limited view */
  if (Context->pattern)
  {
#define THIS_BODY Context->hdrs[j]->content
    if (oldcount || check == M_REOPENED)
    {
      for (j = (check == M_REOPENED) ? 0 : oldcount; j < Context->msgcount; j++)
      {
	if (mutt_pattern_exec (Context->limit_pattern,
			       M_MATCH_FULL_ADDRESS, 
			       Context, Context->hdrs[j]))
	{
	  Context->hdrs[j]->virtual = Context->vcount;
	  Context->v2r[Context->vcount] = j;
	  Context->hdrs[j]->limited = 1;
	  Context->vcount++;
	  Context->vsize += THIS_BODY->length + THIS_BODY->offset - THIS_BODY->hdr_offset;
	}
      }
    }
#undef THIS_BODY
  }
    
  /* save the list of new messages */
  if (oldcount && check != M_REOPENED
      && ((Sort & SORT_MASK) == SORT_THREADS))
  {
    save_new = (HEADER **) safe_malloc (sizeof (HEADER *) * (Context->msgcount - oldcount));
    for (j = oldcount; j < Context->msgcount; j++)
      save_new[j-oldcount] = Context->hdrs[j];
  }
  
  /* if the mailbox was reopened, need to rethread from scratch */
  mutt_sort_headers (Context, (check == M_REOPENED));

  /* uncollapse threads with new mail */
  if ((Sort & SORT_MASK) == SORT_THREADS)
  {
    if (check == M_REOPENED)
    {
      THREAD *h, *j;
      
      Context->collapsed = 0;
      
      for (h = Context->tree; h; h = h->next)
      {
	for (j = h; !j->message; j = j->child)
	  ;
	mutt_uncollapse_thread (Context, j->message);
      }
      mutt_set_virtual (Context);
    }
    else if (oldcount)
    {
      for (j = 0; j < Context->msgcount - oldcount; j++)
      {
	int k;
	
	for (k = 0; k < Context->msgcount; k++)
	{
	  HEADER *h = Context->hdrs[k];
	  if (h == save_new[j] && (!Context->pattern || h->limited))
	    mutt_uncollapse_thread (Context, h);
	}
      }
      FREE (&save_new);
      mutt_set_virtual (Context);
    }
  }
  
  menu->current = -1;
  if (oldcount)
  {
    /* restore the current message to the message it was pointing to */
    for (j = 0; j < Context->vcount; j++)
    {
      if (Context->hdrs[Context->v2r[j]]->index == menu->oldcurrent)
      {
	menu->current = j;
	break;
      }
    }
  }
  
  if (menu->current < 0)
    menu->current = ci_first_message ();
  
}