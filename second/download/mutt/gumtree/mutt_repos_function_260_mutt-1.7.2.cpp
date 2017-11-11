int mutt_reopen_mailbox (CONTEXT *ctx, int *index_hint)
{
  int (*cmp_headers) (const HEADER *, const HEADER *) = NULL;
  HEADER **old_hdrs;
  int old_msgcount;
  int msg_mod = 0;
  int index_hint_set;
  int i, j;
  int rc = -1;

  /* silent operations */
  ctx->quiet = 1;
  
  if (!ctx->quiet)
    mutt_message _("Reopening mailbox...");
  
  /* our heuristics require the old mailbox to be unsorted */
  if (Sort != SORT_ORDER)
  {
    short old_sort;

    old_sort = Sort;
    Sort = SORT_ORDER;
    mutt_sort_headers (ctx, 1);
    Sort = old_sort;
  }

  old_hdrs = NULL;
  old_msgcount = 0;
  
  /* simulate a close */
  if (ctx->id_hash)
    hash_destroy (&ctx->id_hash, NULL);
  if (ctx->subj_hash)
    hash_destroy (&ctx->subj_hash, NULL);
  mutt_clear_threads (ctx);
  FREE (&ctx->v2r);
  if (ctx->readonly)
  {
    for (i = 0; i < ctx->msgcount; i++)
      mutt_free_header (&(ctx->hdrs[i])); /* nothing to do! */
    FREE (&ctx->hdrs);
  }
  else
  {
      /* save the old headers */
    old_msgcount = ctx->msgcount;
    old_hdrs = ctx->hdrs;
    ctx->hdrs = NULL;
  }

  ctx->hdrmax = 0;	/* force allocation of new headers */
  ctx->msgcount = 0;
  ctx->vcount = 0;
  ctx->tagged = 0;
  ctx->deleted = 0;
  ctx->new = 0;
  ctx->unread = 0;
  ctx->flagged = 0;
  ctx->changed = 0;
  ctx->id_hash = NULL;
  ctx->subj_hash = NULL;

  switch (ctx->magic)
  {
    case MUTT_MBOX:
    case MUTT_MMDF:
      cmp_headers = mbox_strict_cmp_headers;
      safe_fclose (&ctx->fp);
      if (!(ctx->fp = safe_fopen (ctx->path, "r")))
	rc = -1;
      else
	rc = ((ctx->magic == MUTT_MBOX) ? mbox_parse_mailbox
	                               : mmdf_parse_mailbox) (ctx);
      break;

    default:
      rc = -1;
      break;
  }
  
  if (rc == -1)
  {
    /* free the old headers */
    for (j = 0; j < old_msgcount; j++)
      mutt_free_header (&(old_hdrs[j]));
    FREE (&old_hdrs);

    ctx->quiet = 0;
    return (-1);
  }

  /* now try to recover the old flags */

  index_hint_set = (index_hint == NULL);

  if (!ctx->readonly)
  {
    for (i = 0; i < ctx->msgcount; i++)
    {
      int found = 0;

      /* some messages have been deleted, and new  messages have been
       * appended at the end; the heuristic is that old messages have then
       * "advanced" towards the beginning of the folder, so we begin the
       * search at index "i"
       */
      for (j = i; j < old_msgcount; j++)
      {
	if (old_hdrs[j] == NULL)
	  continue;
	if (cmp_headers (ctx->hdrs[i], old_hdrs[j]))
	{
	  found = 1;
	  break;
	}
      }
      if (!found)
      {
	for (j = 0; j < i && j < old_msgcount; j++)
	{
	  if (old_hdrs[j] == NULL)
	    continue;
	  if (cmp_headers (ctx->hdrs[i], old_hdrs[j]))
	  {
	    found = 1;
	    break;
	  }
	}
      }

      if (found)
      {
	/* this is best done here */
	if (!index_hint_set && *index_hint == j)
	  *index_hint = i;

	if (old_hdrs[j]->changed)
	{
	  /* Only update the flags if the old header was changed;
	   * otherwise, the header may have been modified externally,
	   * and we don't want to lose _those_ changes
	   */
	  mutt_set_flag (ctx, ctx->hdrs[i], MUTT_FLAG, old_hdrs[j]->flagged);
	  mutt_set_flag (ctx, ctx->hdrs[i], MUTT_REPLIED, old_hdrs[j]->replied);
	  mutt_set_flag (ctx, ctx->hdrs[i], MUTT_OLD, old_hdrs[j]->old);
	  mutt_set_flag (ctx, ctx->hdrs[i], MUTT_READ, old_hdrs[j]->read);
	}
	mutt_set_flag (ctx, ctx->hdrs[i], MUTT_DELETE, old_hdrs[j]->deleted);
	mutt_set_flag (ctx, ctx->hdrs[i], MUTT_PURGE, old_hdrs[j]->purge);
	mutt_set_flag (ctx, ctx->hdrs[i], MUTT_TAG, old_hdrs[j]->tagged);

	/* we don't need this header any more */
	mutt_free_header (&(old_hdrs[j]));
      }
    }

    /* free the remaining old headers */
    for (j = 0; j < old_msgcount; j++)
    {
      if (old_hdrs[j])
      {
	mutt_free_header (&(old_hdrs[j]));
	msg_mod = 1;
      }
    }
    FREE (&old_hdrs);
  }

  ctx->quiet = 0;

  return ((ctx->changed || msg_mod) ? MUTT_REOPENED : MUTT_NEW_MAIL);
}