static void update_index (MUTTMENU *menu, CONTEXT *ctx, int check,
			  int oldcount, int index_hint)
{
  /* store pointers to the newly added messages */
  HEADER  **save_new = NULL;
  int j;

  /* take note of the current message */
  if (oldcount)
  {
    if (menu->current < ctx->vcount)
      menu->oldcurrent = index_hint;
    else
      oldcount = 0; /* invalid message number! */
  }

  /* We are in a limited view. Check if the new message(s) satisfy
   * the limit criteria. If they do, set their virtual msgno so that
   * they will be visible in the limited view */
  if (ctx->pattern)
  {
#define THIS_BODY ctx->hdrs[j]->content
    for (j = (check == M_REOPENED) ? 0 : oldcount; j < ctx->msgcount; j++)
    {
      if (!j)
	ctx->vcount = 0;

      if (mutt_pattern_exec (ctx->limit_pattern,
			     M_MATCH_FULL_ADDRESS,
			     ctx, ctx->hdrs[j]))
      {
	assert (ctx->vcount < ctx->msgcount);
	ctx->hdrs[j]->virtual = ctx->vcount;
	ctx->v2r[ctx->vcount] = j;
	ctx->hdrs[j]->limited = 1;
	ctx->vcount++;
	ctx->vsize += THIS_BODY->length + THIS_BODY->offset - THIS_BODY->hdr_offset;
      }
    }
#undef THIS_BODY
  }

  /* save the list of new messages */
  if (oldcount && check != M_REOPENED
      && ((Sort & SORT_MASK) == SORT_THREADS))
  {
    save_new = (HEADER **) safe_malloc (sizeof (HEADER *) * (ctx->msgcount - oldcount));
    for (j = oldcount; j < ctx->msgcount; j++)
      save_new[j-oldcount] = ctx->hdrs[j];
  }

  /* if the mailbox was reopened, need to rethread from scratch */
  mutt_sort_headers (ctx, (check == M_REOPENED));

  /* uncollapse threads with new mail */
  if ((Sort & SORT_MASK) == SORT_THREADS)
  {
    if (check == M_REOPENED)
    {
      THREAD *h, *j;

      ctx->collapsed = 0;

      for (h = ctx->tree; h; h = h->next)
      {
	for (j = h; !j->message; j = j->child)
	  ;
	mutt_uncollapse_thread (ctx, j->message);
      }
      mutt_set_virtual (ctx);
    }
    else if (oldcount)
    {
      for (j = 0; j < ctx->msgcount - oldcount; j++)
      {
	int k;

	for (k = 0; k < ctx->msgcount; k++)
	{
	  HEADER *h = ctx->hdrs[k];
	  if (h == save_new[j] && (!ctx->pattern || h->limited))
	    mutt_uncollapse_thread (ctx, h);
	}
      }
      FREE (&save_new);
      mutt_set_virtual (ctx);
    }
  }

  menu->current = -1;
  if (oldcount)
  {
    /* restore the current message to the message it was pointing to */
    for (j = 0; j < ctx->vcount; j++)
    {
      if (ctx->hdrs[ctx->v2r[j]]->index == menu->oldcurrent)
      {
	menu->current = j;
	break;
      }
    }
  }

  if (menu->current < 0)
    menu->current = ci_first_message ();

}