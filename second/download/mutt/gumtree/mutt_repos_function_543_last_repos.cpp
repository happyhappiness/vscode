int mx_close_mailbox (CONTEXT *ctx, int *index_hint)
{
  int i, move_messages = 0, purge = 1, read_msgs = 0;
  int check;
  int isSpool = 0;
  CONTEXT f;
  char mbox[_POSIX_PATH_MAX];
  char buf[SHORT_STRING];

  if (!ctx) return 0;

  ctx->closing = 1;

  if (ctx->readonly || ctx->dontwrite || ctx->append)
  {
    mx_fastclose_mailbox (ctx);
    return 0;
  }

  for (i = 0; i < ctx->msgcount; i++)
  {
    if (!ctx->hdrs[i]->deleted && ctx->hdrs[i]->read 
        && !(ctx->hdrs[i]->flagged && option (OPTKEEPFLAGGED)))
      read_msgs++;
  }

  if (read_msgs && quadoption (OPT_MOVE) != MUTT_NO)
  {
    char *p;

    if ((p = mutt_find_hook (MUTT_MBOXHOOK, ctx->path)))
    {
      isSpool = 1;
      strfcpy (mbox, p, sizeof (mbox));
    }
    else
    {
      strfcpy (mbox, NONULL(Inbox), sizeof (mbox));
      isSpool = mutt_is_spool (ctx->path) && !mutt_is_spool (mbox);
    }

    if (isSpool && *mbox)
    {
      mutt_expand_path (mbox, sizeof (mbox));
      snprintf (buf, sizeof (buf), _("Move read messages to %s?"), mbox);
      if ((move_messages = query_quadoption (OPT_MOVE, buf)) == -1)
      {
	ctx->closing = 0;
	return (-1);
      }
    }
  }

  /* 
   * There is no point in asking whether or not to purge if we are
   * just marking messages as "trash".
   */
  if (ctx->deleted && !(ctx->magic == MUTT_MAILDIR && option (OPTMAILDIRTRASH)))
  {
    snprintf (buf, sizeof (buf), ctx->deleted == 1
	     ? _("Purge %d deleted message?") : _("Purge %d deleted messages?"),
	      ctx->deleted);
    if ((purge = query_quadoption (OPT_DELETE, buf)) < 0)
    {
      ctx->closing = 0;
      return (-1);
    }
  }

  if (option (OPTMARKOLD))
  {
    for (i = 0; i < ctx->msgcount; i++)
    {
      if (!ctx->hdrs[i]->deleted && !ctx->hdrs[i]->old && !ctx->hdrs[i]->read)
	mutt_set_flag (ctx, ctx->hdrs[i], MUTT_OLD, 1);
    }
  }

  if (move_messages)
  {
    if (!ctx->quiet)
      mutt_message (_("Moving read messages to %s..."), mbox);

#ifdef USE_IMAP
    /* try to use server-side copy first */
    i = 1;
    
    if (ctx->magic == MUTT_IMAP && mx_is_imap (mbox))
    {
      /* tag messages for moving, and clear old tags, if any */
      for (i = 0; i < ctx->msgcount; i++)
	if (ctx->hdrs[i]->read && !ctx->hdrs[i]->deleted
            && !(ctx->hdrs[i]->flagged && option (OPTKEEPFLAGGED))) 
	  ctx->hdrs[i]->tagged = 1;
	else
	  ctx->hdrs[i]->tagged = 0;
      
      i = imap_copy_messages (ctx, NULL, mbox, 1);
    }
    
    if (i == 0) /* success */
      mutt_clear_error ();
    else if (i == -1) /* horrible error, bail */
    {
      ctx->closing=0;
      return -1;
    }
    else /* use regular append-copy mode */
#endif
    {
      if (mx_open_mailbox (mbox, MUTT_APPEND, &f) == NULL)
      {
	ctx->closing = 0;
	return -1;
      }

      for (i = 0; i < ctx->msgcount; i++)
      {
	if (ctx->hdrs[i]->read && !ctx->hdrs[i]->deleted
            && !(ctx->hdrs[i]->flagged && option (OPTKEEPFLAGGED)))
        {
	  if (mutt_append_message (&f, ctx, ctx->hdrs[i], 0, CH_UPDATE_LEN) == 0)
	  {
	    mutt_set_flag (ctx, ctx->hdrs[i], MUTT_DELETE, 1);
	    mutt_set_flag (ctx, ctx->hdrs[i], MUTT_PURGE, 1);
	  }
	  else
	  {
	    mx_close_mailbox (&f, NULL);
	    ctx->closing = 0;
	    return -1;
	  }
	}
      }
    
      mx_close_mailbox (&f, NULL);
    }
    
  }
  else if (!ctx->changed && ctx->deleted == 0)
  {
    if (!ctx->quiet)
      mutt_message _("Mailbox is unchanged.");
    if (ctx->magic == MUTT_MBOX || ctx->magic == MUTT_MMDF)
      mbox_reset_atime (ctx, NULL);
    mx_fastclose_mailbox (ctx);
    return 0;
  }

  /* copy mails to the trash before expunging */
  if (purge && ctx->deleted && mutt_strcmp (ctx->path, TrashPath))
  {
    if (trash_append (ctx) != 0)
    {
      ctx->closing = 0;
      return -1;
    }
  }

#ifdef USE_IMAP
  /* allow IMAP to preserve the deleted flag across sessions */
  if (ctx->magic == MUTT_IMAP)
  {
    if ((check = imap_sync_mailbox (ctx, purge, index_hint)) != 0)
    {
      ctx->closing = 0;
      return check;
    }
  }
  else
#endif
  {
    if (!purge)
    {
      for (i = 0; i < ctx->msgcount; i++)
      {
        ctx->hdrs[i]->deleted = 0;
        ctx->hdrs[i]->purge = 0;
      }
      ctx->deleted = 0;
    }

    if (ctx->changed || ctx->deleted)
    {
      if ((check = sync_mailbox (ctx, index_hint)) != 0)
      {
	ctx->closing = 0;
	return check;
      }
    }
  }

  if (!ctx->quiet)
  {
    if (move_messages)
      mutt_message (_("%d kept, %d moved, %d deleted."),
	ctx->msgcount - ctx->deleted, read_msgs, ctx->deleted);
    else
      mutt_message (_("%d kept, %d deleted."),
	ctx->msgcount - ctx->deleted, ctx->deleted);
  }

  if (ctx->msgcount == ctx->deleted &&
      (ctx->magic == MUTT_MMDF || ctx->magic == MUTT_MBOX) &&
      !mutt_is_spool(ctx->path) && !option (OPTSAVEEMPTY))
    mx_unlink_empty (ctx->path);

#ifdef USE_SIDEBAR
  if (purge && ctx->deleted)
  {
    int orig_msgcount = ctx->msgcount;

    for (i = 0; i < ctx->msgcount; i++)
    {
      if (ctx->hdrs[i]->deleted && !ctx->hdrs[i]->read)
        ctx->unread--;
      if (ctx->hdrs[i]->deleted && ctx->hdrs[i]->flagged)
        ctx->flagged--;
    }
    ctx->msgcount -= ctx->deleted;
    mutt_sb_set_buffystats (ctx);
    ctx->msgcount = orig_msgcount;
  }
#endif

  mx_fastclose_mailbox (ctx);

  return 0;
}