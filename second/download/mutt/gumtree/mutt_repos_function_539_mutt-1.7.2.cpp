int mx_sync_mailbox (CONTEXT *ctx, int *index_hint)
{
  int rc, i;
  int purge = 1;
  int msgcount, deleted;

  if (ctx->dontwrite)
  {
    char buf[STRING], tmp[STRING];
    if (km_expand_key (buf, sizeof(buf),
                       km_find_func (MENU_MAIN, OP_TOGGLE_WRITE)))
      snprintf (tmp, sizeof(tmp), _(" Press '%s' to toggle write"), buf);
    else
      strfcpy (tmp, _("Use 'toggle-write' to re-enable write!"), sizeof(tmp));

    mutt_error (_("Mailbox is marked unwritable. %s"), tmp);
    return -1;
  }
  else if (ctx->readonly)
  {
    mutt_error _("Mailbox is read-only.");
    return -1;
  }

  if (!ctx->changed && !ctx->deleted)
  {
    if (!ctx->quiet)
      mutt_message _("Mailbox is unchanged.");
    return (0);
  }

  if (ctx->deleted)
  {
    char buf[SHORT_STRING];

    snprintf (buf, sizeof (buf), ctx->deleted == 1
	     ? _("Purge %d deleted message?") : _("Purge %d deleted messages?"),
	      ctx->deleted);
    if ((purge = query_quadoption (OPT_DELETE, buf)) < 0)
      return (-1);
    else if (purge == MUTT_NO)
    {
      if (!ctx->changed)
	return 0; /* nothing to do! */
      /* let IMAP servers hold on to D flags */
      if (ctx->magic != MUTT_IMAP)
      {
        for (i = 0 ; i < ctx->msgcount ; i++)
        {
          ctx->hdrs[i]->deleted = 0;
          ctx->hdrs[i]->purge = 0;
        }
        ctx->deleted = 0;
      }
    }
    else if (ctx->last_tag && ctx->last_tag->deleted)
      ctx->last_tag = NULL; /* reset last tagged msg now useless */
  }

  /* really only for IMAP - imap_sync_mailbox results in a call to
   * mx_update_tables, so ctx->deleted is 0 when it comes back */
  msgcount = ctx->msgcount;
  deleted = ctx->deleted;

  if (purge && ctx->deleted && mutt_strcmp (ctx->path, TrashPath))
  {
    if (trash_append (ctx) != 0)
      return -1;
  }

#ifdef USE_IMAP
  if (ctx->magic == MUTT_IMAP)
    rc = imap_sync_mailbox (ctx, purge, index_hint);
  else
#endif
    rc = sync_mailbox (ctx, index_hint);
  if (rc == 0)
  {
#ifdef USE_IMAP
    if (ctx->magic == MUTT_IMAP && !purge)
    {
      if (!ctx->quiet)
        mutt_message _("Mailbox checkpointed.");
    }
    else
#endif
    {
      if (!ctx->quiet)
	mutt_message (_("%d kept, %d deleted."), msgcount - deleted,
		      deleted);
    }

    mutt_sleep (0);
    
    if (ctx->msgcount == ctx->deleted &&
	(ctx->magic == MUTT_MBOX || ctx->magic == MUTT_MMDF) &&
	!mutt_is_spool (ctx->path) && !option (OPTSAVEEMPTY))
    {
      unlink (ctx->path);
      mx_fastclose_mailbox (ctx);
      return 0;
    }

    /* if we haven't deleted any messages, we don't need to resort */
    /* ... except for certain folder formats which need "unsorted" 
     * sort order in order to synchronize folders.
     * 
     * MH and maildir are safe.  mbox-style seems to need re-sorting,
     * at least with the new threading code.
     */
    if (purge || (ctx->magic != MUTT_MAILDIR && ctx->magic != MUTT_MH))
    {
      /* IMAP does this automatically after handling EXPUNGE */
      if (ctx->magic != MUTT_IMAP)
      {
	mx_update_tables (ctx, 1);
	mutt_sort_headers (ctx, 1); /* rethread from scratch */
      }
    }
  }

  return (rc);
}