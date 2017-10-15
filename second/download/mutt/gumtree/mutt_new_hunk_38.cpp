      count++;
      if (setstart == 0)
      {
        setstart = HEADER_DATA (hdrs[n])->uid;
        if (started == 0)
	{
	  mutt_buffer_printf (buf, "%u", HEADER_DATA (hdrs[n])->uid);
	  started = 1;
	}
        else
	  mutt_buffer_printf (buf, ",%u", HEADER_DATA (hdrs[n])->uid);
      }
      /* tie up if the last message also matches */
      else if (n == idata->ctx->msgcount-1)
	mutt_buffer_printf (buf, ":%u", HEADER_DATA (hdrs[n])->uid);
    }
    /* End current set if message doesn't match or we've reached the end
     * of the mailbox via inactive messages following the last match. */
    else if (setstart && (hdrs[n]->active || n == idata->ctx->msgcount-1))
    {
      if (HEADER_DATA (hdrs[n-1])->uid > setstart)
	mutt_buffer_printf (buf, ":%u", HEADER_DATA (hdrs[n-1])->uid);
      setstart = 0;
    }
  }

  *pos = n;

  return count;
}

/* Prepares commands for all messages matching conditions (must be flushed
 * with imap_exec)
 * Params:
 *   idata: IMAP_DATA containing context containing header set
 *   pre, post: commands are of the form "%s %s %s %s", tag,
 *     pre, message set, post
 *   flag: enum of flag type on which to filter
 *   changed: include only changed messages in message set
 *   invert: invert sense of flag, eg M_READ matches unread messages
 * Returns: number of matched messages, or -1 on failure */
int imap_exec_msgset (IMAP_DATA* idata, const char* pre, const char* post,
                      int flag, int changed, int invert)
{
  HEADER** hdrs = NULL;
  short oldsort;
  BUFFER* cmd;
  int pos;
  int rc;
  int count = 0;

  if (! (cmd = mutt_buffer_new ()))
  {
    dprint (1, (debugfile, "imap_exec_msgset: unable to allocate buffer\n"));
    return -1;
  }

  /* We make a copy of the headers just in case resorting doesn't give
   exactly the original order (duplicate messages?), because other parts of
   the ctx are tied to the header order. This may be overkill. */
  oldsort = Sort;
  if (Sort != SORT_ORDER)
  {
    hdrs = idata->ctx->hdrs;
    idata->ctx->hdrs = safe_malloc (idata->ctx->msgcount * sizeof (HEADER*));
    memcpy (idata->ctx->hdrs, hdrs, idata->ctx->msgcount * sizeof (HEADER*));

    Sort = SORT_ORDER;
    qsort (idata->ctx->hdrs, idata->ctx->msgcount, sizeof (HEADER*),
           mutt_get_sort_func (SORT_ORDER));
  }

  pos = 0;

  do
  {
    cmd->dptr = cmd->data;
    mutt_buffer_printf (cmd, "%s ", pre);
    rc = imap_make_msg_set (idata, cmd, flag, changed, invert, &pos);
    if (rc > 0)
    {
      mutt_buffer_printf (cmd, " %s", post);
      if (imap_exec (idata, cmd->data, IMAP_CMD_QUEUE))
      {
	rc = -1;
	goto out;
      }
      count += rc;
    }
  }
  while (rc > 0);

  rc = count;

out:
  mutt_buffer_free (&cmd);
  if (oldsort != Sort)
  {
    Sort = oldsort;
    FREE (&idata->ctx->hdrs);
    idata->ctx->hdrs = hdrs;
  }

  return rc;
}

/* returns 0 if mutt's flags match cached server flags */
static int compare_flags (HEADER* h)
{
  IMAP_HEADER_DATA* hd = (IMAP_HEADER_DATA*)h->data;

  if (h->read != hd->read)
    return 1;
  if (h->old != hd->old)
    return 1;
  if (h->flagged != hd->flagged)
    return 1;
  if (h->replied != hd->replied)
    return 1;
  if (h->deleted != hd->deleted)
    return 1;

  return 0;
}

/* Update the IMAP server to reflect the flags a single message.  */
int imap_sync_message (IMAP_DATA *idata, HEADER *hdr, BUFFER *cmd,
		       int *err_continue)
{
  char flags[LONG_STRING];
  char uid[11];

  hdr->changed = 0;

  if (!compare_flags (hdr))
  {
    idata->ctx->changed--;
    return 0;
  }

  snprintf (uid, sizeof (uid), "%u", HEADER_DATA(hdr)->uid);
  cmd->dptr = cmd->data;
  mutt_buffer_addstr (cmd, "UID STORE ");
  mutt_buffer_addstr (cmd, uid);

  flags[0] = '\0';

  imap_set_flag (idata, M_ACL_SEEN, hdr->read, "\\Seen ",
		 flags, sizeof (flags));
  imap_set_flag (idata, M_ACL_WRITE, hdr->old,
                 "Old ", flags, sizeof (flags));
  imap_set_flag (idata, M_ACL_WRITE, hdr->flagged,
		 "\\Flagged ", flags, sizeof (flags));
  imap_set_flag (idata, M_ACL_WRITE, hdr->replied,
		 "\\Answered ", flags, sizeof (flags));
  imap_set_flag (idata, M_ACL_DELETE, hdr->deleted,
		 "\\Deleted ", flags, sizeof (flags));

  /* now make sure we don't lose custom tags */
  if (mutt_bit_isset (idata->ctx->rights, M_ACL_WRITE))
    imap_add_keywords (flags, hdr, idata->flags, sizeof (flags));

  mutt_remove_trailing_ws (flags);

  /* UW-IMAP is OK with null flags, Cyrus isn't. The only solution is to
   * explicitly revoke all system flags (if we have permission) */
  if (!*flags)
  {
    imap_set_flag (idata, M_ACL_SEEN, 1, "\\Seen ", flags, sizeof (flags));
    imap_set_flag (idata, M_ACL_WRITE, 1, "Old ", flags, sizeof (flags));
    imap_set_flag (idata, M_ACL_WRITE, 1, "\\Flagged ", flags, sizeof (flags));
    imap_set_flag (idata, M_ACL_WRITE, 1, "\\Answered ", flags, sizeof (flags));
    imap_set_flag (idata, M_ACL_DELETE, 1, "\\Deleted ", flags, sizeof (flags));

    mutt_remove_trailing_ws (flags);

    mutt_buffer_addstr (cmd, " -FLAGS.SILENT (");
  } else
    mutt_buffer_addstr (cmd, " FLAGS.SILENT (");

  mutt_buffer_addstr (cmd, flags);
  mutt_buffer_addstr (cmd, ")");

  /* dumb hack for bad UW-IMAP 4.7 servers spurious FLAGS updates */
  hdr->active = 0;

  /* after all this it's still possible to have no flags, if you
   * have no ACL rights */
  if (*flags && (imap_exec (idata, cmd->data, 0) != 0) &&
      err_continue && (*err_continue != M_YES))
  {
    *err_continue = imap_continue ("imap_sync_message: STORE failed",
				   idata->buf);
    if (*err_continue != M_YES)
      return -1;
  }

  hdr->active = 1;
  idata->ctx->changed--;

  return 0;
}

static int sync_helper (IMAP_DATA* idata, int right, int flag, const char* name)
{
  int count = 0;
  int rc;

  char buf[LONG_STRING];

  if (!mutt_bit_isset (idata->ctx->rights, right))
    return 0;

  if (right == M_ACL_WRITE && !imap_has_flag (idata->flags, name))
    return 0;

  snprintf (buf, sizeof(buf), "+FLAGS.SILENT (%s)", name);
  if ((rc = imap_exec_msgset (idata, "UID STORE", buf, flag, 1, 0)) < 0)
    return rc;
  count += rc;

  buf[0] = '-';
  if ((rc = imap_exec_msgset (idata, "UID STORE", buf, flag, 1, 1)) < 0)
    return rc;
  count += rc;

  return count;
}

/* update the IMAP server to reflect message changes done within mutt.
 * Arguments
 *   ctx: the current context
 *   expunge: 0 or 1 - do expunge?
 */
int imap_sync_mailbox (CONTEXT* ctx, int expunge, int* index_hint)
{
  IMAP_DATA* idata;
  CONTEXT* appendctx = NULL;
  HEADER* h;
  HEADER** hdrs = NULL;
  int oldsort;
  int n;
  int rc;

  idata = (IMAP_DATA*) ctx->data;

  if (idata->state < IMAP_SELECTED)
  {
    dprint (2, (debugfile, "imap_sync_mailbox: no mailbox selected\n"));
    return -1;
  }

  /* This function is only called when the calling code expects the context
   * to be changed. */
  imap_allow_reopen (ctx);

  if ((rc = imap_check_mailbox (ctx, index_hint, 0)) != 0)
    return rc;

  /* if we are expunging anyway, we can do deleted messages very quickly... */
  if (expunge && mutt_bit_isset (ctx->rights, M_ACL_DELETE))
  {
    if ((rc = imap_exec_msgset (idata, "UID STORE", "+FLAGS.SILENT (\\Deleted)",
                                M_DELETED, 1, 0)) < 0)
    {
      mutt_error (_("Expunge failed"));
      mutt_sleep (1);
      goto out;
    }

    if (rc > 0)
    {
      /* mark these messages as unchanged so second pass ignores them. Done
       * here so BOGUS UW-IMAP 4.7 SILENT FLAGS updates are ignored. */
      for (n = 0; n < ctx->msgcount; n++)
        if (ctx->hdrs[n]->deleted && ctx->hdrs[n]->changed)
          ctx->hdrs[n]->active = 0;
      mutt_message (_("Marking %d messages deleted..."), rc);
    }
  }

#if USE_HCACHE
  idata->hcache = imap_hcache_open (idata, NULL);
#endif

  /* save messages with real (non-flag) changes */
  for (n = 0; n < ctx->msgcount; n++)
  {
    h = ctx->hdrs[n];

    if (h->deleted)
    {
      imap_cache_del (idata, h);
#if USE_HCACHE
      imap_hcache_del (idata, HEADER_DATA(h)->uid);
#endif
    }

    if (h->active && h->changed)
    {
#if USE_HCACHE
      imap_hcache_put (idata, h);
#endif
      /* if the message has been rethreaded or attachments have been deleted
       * we delete the message and reupload it.
       * This works better if we're expunging, of course. */
      if ((h->env && (h->env->refs_changed || h->env->irt_changed)) ||
	  h->attach_del)
      {
        mutt_message (_("Saving changed messages... [%d/%d]"), n+1,
                      ctx->msgcount);
	if (!appendctx)
	  appendctx = mx_open_mailbox (ctx->path, M_APPEND | M_QUIET, NULL);
	if (!appendctx)
	  dprint (1, (debugfile, "imap_sync_mailbox: Error opening mailbox in append mode\n"));
	else
	  _mutt_save_message (h, appendctx, 1, 0, 0);
      }
    }
  }

#if USE_HCACHE
  imap_hcache_close (idata);
#endif

  /* sync +/- flags for the five flags mutt cares about */
  rc = 0;

  /* presort here to avoid doing 10 resorts in imap_exec_msgset */
  oldsort = Sort;
  if (Sort != SORT_ORDER)
  {
    hdrs = ctx->hdrs;
    ctx->hdrs = safe_malloc (ctx->msgcount * sizeof (HEADER*));
    memcpy (ctx->hdrs, hdrs, ctx->msgcount * sizeof (HEADER*));

    Sort = SORT_ORDER;
    qsort (ctx->hdrs, ctx->msgcount, sizeof (HEADER*),
           mutt_get_sort_func (SORT_ORDER));
  }

  rc += sync_helper (idata, M_ACL_DELETE, M_DELETED, "\\Deleted");
  rc += sync_helper (idata, M_ACL_WRITE, M_FLAG, "\\Flagged");
  rc += sync_helper (idata, M_ACL_WRITE, M_OLD, "Old");
  rc += sync_helper (idata, M_ACL_SEEN, M_READ, "\\Seen");
  rc += sync_helper (idata, M_ACL_WRITE, M_REPLIED, "\\Answered");

  if (oldsort != Sort)
  {
    Sort = oldsort;
    FREE (&ctx->hdrs);
    ctx->hdrs = hdrs;
  }

  if (rc && (imap_exec (idata, NULL, 0) != IMAP_CMD_OK))
  {
    if (ctx->closing)
    {
      if (mutt_yesorno (_("Error saving flags. Close anyway?"), 0) == M_YES)
      {
        rc = 0;
        idata->state = IMAP_AUTHENTICATED;
        goto out;
      }
    }
    else
      mutt_error _("Error saving flags");
    goto out;
  }

  for (n = 0; n < ctx->msgcount; n++)
    ctx->hdrs[n]->changed = 0;
  ctx->changed = 0;

  /* We must send an EXPUNGE command if we're not closing. */
  if (expunge && !(ctx->closing) &&
      mutt_bit_isset(ctx->rights, M_ACL_DELETE))
  {
    mutt_message _("Expunging messages from server...");
    /* Set expunge bit so we don't get spurious reopened messages */
    idata->reopen |= IMAP_EXPUNGE_EXPECTED;
    if (imap_exec (idata, "EXPUNGE", 0) != 0)
    {
      imap_error (_("imap_sync_mailbox: EXPUNGE failed"), idata->buf);
      rc = -1;
      goto out;
    }
  }

  if (expunge && ctx->closing)
  {
    imap_exec (idata, "CLOSE", IMAP_CMD_QUEUE);
    idata->state = IMAP_AUTHENTICATED;
  }

  if (option (OPTMESSAGECACHECLEAN))
    imap_cache_clean (idata);

  rc = 0;

 out:
  if (appendctx)
  {
    mx_fastclose_mailbox (appendctx);
    FREE (&appendctx);
  }
  return rc;
}

/* imap_close_mailbox: clean up IMAP data in CONTEXT */
int imap_close_mailbox (CONTEXT* ctx)
{
  IMAP_DATA* idata;
  int i;

  idata = (IMAP_DATA*) ctx->data;
  /* Check to see if the mailbox is actually open */
  if (!idata)
    return 0;

  if (ctx == idata->ctx)
  {
    if (idata->status != IMAP_FATAL && idata->state >= IMAP_SELECTED)
    {
      /* mx_close_mailbox won't sync if there are no deleted messages
       * and the mailbox is unchanged, so we may have to close here */
      if (!ctx->deleted)
        imap_exec (idata, "CLOSE", IMAP_CMD_QUEUE);
      idata->state = IMAP_AUTHENTICATED;
    }

    idata->reopen &= IMAP_REOPEN_ALLOW;
    FREE (&(idata->mailbox));
    mutt_free_list (&idata->flags);
    idata->ctx = NULL;
  }

  /* free IMAP part of headers */
  for (i = 0; i < ctx->msgcount; i++)
    /* mailbox may not have fully loaded */
    if (ctx->hdrs[i] && ctx->hdrs[i]->data)
      imap_free_header_data ((IMAP_HEADER_DATA**)&(ctx->hdrs[i]->data));

  for (i = 0; i < IMAP_CACHE_LEN; i++)
  {
    if (idata->cache[i].path)
    {
      unlink (idata->cache[i].path);
      FREE (&idata->cache[i].path);
    }
  }

  mutt_bcache_close (&idata->bcache);

  return 0;
}

/* use the NOOP or IDLE command to poll for new mail
 *
 * return values:
 *	M_REOPENED	mailbox has been externally modified
 *	M_NEW_MAIL	new mail has arrived!
 *	0		no change
 *	-1		error
 */
int imap_check_mailbox (CONTEXT *ctx, int *index_hint, int force)
{
  /* overload keyboard timeout to avoid many mailbox checks in a row.
   * Most users don't like having to wait exactly when they press a key. */
  IMAP_DATA* idata;
  int result = 0;

  idata = (IMAP_DATA*) ctx->data;

  /* try IDLE first, unless force is set */
  if (!force && option (OPTIMAPIDLE) && mutt_bit_isset (idata->capabilities, IDLE)
      && (idata->state != IMAP_IDLE || time(NULL) >= idata->lastread + ImapKeepalive))
  {
    if (imap_cmd_idle (idata) < 0)
      return -1;
  }
  if (idata->state == IMAP_IDLE)
  {
    while ((result = mutt_socket_poll (idata->conn)) > 0)
    {
      if (imap_cmd_step (idata) != IMAP_CMD_CONTINUE)
      {
        dprint (1, (debugfile, "Error reading IDLE response\n"));
        return -1;
      }
    }
    if (result < 0)
    {
      dprint (1, (debugfile, "Poll failed, disabling IDLE\n"));
      mutt_bit_unset (idata->capabilities, IDLE);
    }
  }

  if ((force ||
       (idata->state != IMAP_IDLE && time(NULL) >= idata->lastread + Timeout))
      && imap_exec (idata, "NOOP", 0) != 0)
    return -1;

  /* We call this even when we haven't run NOOP in case we have pending
   * changes to process, since we can reopen here. */
  imap_cmd_finish (idata);

  if (idata->check_status & IMAP_EXPUNGE_PENDING)
