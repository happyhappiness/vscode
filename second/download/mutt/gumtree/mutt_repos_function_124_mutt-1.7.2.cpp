void mutt_sort_headers (CONTEXT *ctx, int init)
{
  int i;
  HEADER *h;
  THREAD *thread, *top;
  sort_t *sortfunc;
  
  unset_option (OPTNEEDRESORT);

  if (!ctx)
    return;

  if (!ctx->msgcount)
  {
    /* this function gets called by mutt_sync_mailbox(), which may have just
     * deleted all the messages.  the virtual message numbers are not updated
     * in that routine, so we must make sure to zero the vcount member.
     */
    ctx->vcount = 0;
    mutt_clear_threads (ctx);
    return; /* nothing to do! */
  }

  if (!ctx->quiet)
    mutt_message _("Sorting mailbox...");

  if (option (OPTNEEDRESCORE) && option (OPTSCORE))
  {
    for (i = 0; i < ctx->msgcount; i++)
      mutt_score_message (ctx, ctx->hdrs[i], 1);
  }
  unset_option (OPTNEEDRESCORE);

  if (option (OPTRESORTINIT))
  {
    unset_option (OPTRESORTINIT);
    init = 1;
  }

  if (init && ctx->tree)
    mutt_clear_threads (ctx);

  if ((Sort & SORT_MASK) == SORT_THREADS)
  {
    AuxSort = NULL;
    /* if $sort_aux changed after the mailbox is sorted, then all the
       subthreads need to be resorted */
    if (option (OPTSORTSUBTHREADS))
    {
      i = Sort;
      Sort = SortAux;
      if (ctx->tree)
	ctx->tree = mutt_sort_subthreads (ctx->tree, 1);
      Sort = i;
      unset_option (OPTSORTSUBTHREADS);
    }
    mutt_sort_threads (ctx, init);
  }
  else if ((sortfunc = mutt_get_sort_func (Sort)) == NULL ||
	   (AuxSort = mutt_get_sort_func (SortAux)) == NULL)
  {
    mutt_error _("Could not find sorting function! [report this bug]");
    mutt_sleep (1);
    return;
  }
  else 
    qsort ((void *) ctx->hdrs, ctx->msgcount, sizeof (HEADER *), sortfunc);

  /* adjust the virtual message numbers */
  ctx->vcount = 0;
  for (i = 0; i < ctx->msgcount; i++)
  {
    HEADER *cur = ctx->hdrs[i];
    if (cur->virtual != -1 || (cur->collapsed && (!ctx->pattern || cur->limited)))
    {
      cur->virtual = ctx->vcount;
      ctx->v2r[ctx->vcount] = i;
      ctx->vcount++;
    }
    cur->msgno = i;
  }

  /* re-collapse threads marked as collapsed */
  if ((Sort & SORT_MASK) == SORT_THREADS)
  {
    top = ctx->tree;
    while ((thread = top) != NULL)
    {
      while (!thread->message)
	thread = thread->child;
      h = thread->message;

      if (h->collapsed)
	mutt_collapse_thread (ctx, h);
      top = top->next;
    }
    mutt_set_virtual (ctx);
  }

  if (!ctx->quiet)
    mutt_clear_error ();
}