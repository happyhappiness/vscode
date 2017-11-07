int imap_sync_mailbox (CONTEXT* ctx, int expunge, int* index_hint)
{
  IMAP_DATA* idata;
  CONTEXT* appendctx = NULL;
  BUFFER cmd;
  char flags[LONG_STRING];
  char uid[11];
  int deleted;
  int n;
  int err_continue = M_NO;	/* continue on error? */
  int rc;

  idata = (IMAP_DATA*) ctx->data;

  if (idata->state != IMAP_SELECTED)
  {
    dprint (2, (debugfile, "imap_sync_mailbox: no mailbox selected\n"));
    return -1;
  }

  /* CLOSE purges deleted messages. If we don't want to purge them, we must
   * tell imap_close_mailbox not to issue the CLOSE command */
  if (expunge)
    idata->noclose = 0;
  else
    idata->noclose = 1;

  /* This function is only called when the calling code	expects the context
   * to be changed. */
  imap_allow_reopen (ctx);

  if ((rc = imap_check_mailbox (ctx, index_hint)) != 0)
    return rc;

  memset (&cmd, 0, sizeof (cmd));

  /* if we are expunging anyway, we can do deleted messages very quickly... */
  if (expunge && mutt_bit_isset (idata->rights, IMAP_ACL_DELETE))
  {
    mutt_buffer_addstr (&cmd, "UID STORE ");
    deleted = imap_make_msg_set (idata, &cmd, M_DELETE, 1);

    /* if we have a message set, then let's delete */
    if (deleted)
    {
      mutt_message (_("Marking %d messages deleted..."), deleted);
      mutt_buffer_addstr (&cmd, " +FLAGS.SILENT (\\Deleted)");
      /* mark these messages as unchanged so second pass ignores them. Done
       * here so BOGUS UW-IMAP 4.7 SILENT FLAGS updates are ignored. */
      for (n = 0; n < ctx->msgcount; n++)
	if (ctx->hdrs[n]->deleted && ctx->hdrs[n]->changed)
	  ctx->hdrs[n]->active = 0;
      if (imap_exec (idata, cmd.data, 0) != 0)
      {
	mutt_error (_("Expunge failed"));
	mutt_sleep (1);
	rc = -1;
	goto out;
      }
    }
  }

  /* save status changes */
  for (n = 0; n < ctx->msgcount; n++)
  {
    if (ctx->hdrs[n]->active && ctx->hdrs[n]->changed)
    {
      ctx->hdrs[n]->changed = 0;

      mutt_message (_("Saving message status flags... [%d/%d]"), n+1,
        ctx->msgcount);

      snprintf (uid, sizeof (uid), "%u", HEADER_DATA(ctx->hdrs[n])->uid);
      cmd.dptr = cmd.data;
      mutt_buffer_addstr (&cmd, "UID STORE ");
      mutt_buffer_addstr (&cmd, uid);

      /* if attachments have been deleted we delete the message and reupload
       * it. This works better if we're expunging, of course. */
      if (ctx->hdrs[n]->attach_del)
      {
	dprint (3, (debugfile, "imap_sync_mailbox: Attachments to be deleted, falling back to _mutt_save_message\n"));
	if (!appendctx)
	  appendctx = mx_open_mailbox (ctx->path, M_APPEND | M_QUIET, NULL);
	if (!appendctx)
	{
	  dprint (1, (debugfile, "imap_sync_mailbox: Error opening mailbox in append mode\n"));
	}
	else
	  _mutt_save_message (ctx->hdrs[n], appendctx, 1, 0, 0);
      }
      flags[0] = '\0';
      
      imap_set_flag (idata, IMAP_ACL_SEEN, ctx->hdrs[n]->read, "\\Seen ",
        flags, sizeof (flags));
      imap_set_flag (idata, IMAP_ACL_WRITE, ctx->hdrs[n]->flagged,
        "\\Flagged ", flags, sizeof (flags));
      imap_set_flag (idata, IMAP_ACL_WRITE, ctx->hdrs[n]->replied,
        "\\Answered ", flags, sizeof (flags));
      imap_set_flag (idata, IMAP_ACL_DELETE, ctx->hdrs[n]->deleted,
        "\\Deleted ", flags, sizeof (flags));

      /* now make sure we don't lose custom tags */
      if (mutt_bit_isset (idata->rights, IMAP_ACL_WRITE))
        imap_add_keywords (flags, ctx->hdrs[n], idata->flags, sizeof (flags));
      
      mutt_remove_trailing_ws (flags);
      
      /* UW-IMAP is OK with null flags, Cyrus isn't. The only solution is to
       * explicitly revoke all system flags (if we have permission) */
      if (!*flags)
      {
        imap_set_flag (idata, IMAP_ACL_SEEN, 1, "\\Seen ", flags, sizeof (flags));
        imap_set_flag (idata, IMAP_ACL_WRITE, 1, "\\Flagged ", flags, sizeof (flags));
        imap_set_flag (idata, IMAP_ACL_WRITE, 1, "\\Answered ", flags, sizeof (flags));
        imap_set_flag (idata, IMAP_ACL_DELETE, 1, "\\Deleted ", flags, sizeof (flags));

        mutt_remove_trailing_ws (flags);

	mutt_buffer_addstr (&cmd, " -FLAGS.SILENT (");
      }
      else
	mutt_buffer_addstr (&cmd, " FLAGS.SILENT (");
      
      mutt_buffer_addstr (&cmd, flags);
      mutt_buffer_addstr (&cmd, ")");

      /* dumb hack for bad UW-IMAP 4.7 servers spurious FLAGS updates */
      ctx->hdrs[n]->active = 0;

      /* after all this it's still possible to have no flags, if you
       * have no ACL rights */
      if (*flags && (imap_exec (idata, cmd.data, 0) != 0) &&
        (err_continue != M_YES))
      {
        err_continue = imap_continue ("imap_sync_mailbox: STORE failed",
          idata->cmd.buf);
        if (err_continue != M_YES)
	{
	  rc = -1;
	  goto out;
	}
      }

      ctx->hdrs[n]->active = 1;
    }
  }
  ctx->changed = 0;

  /* We must send an EXPUNGE command if we're not closing. */
  if (expunge && !(ctx->closing) &&
      mutt_bit_isset(idata->rights, IMAP_ACL_DELETE))
  {
    mutt_message _("Expunging messages from server...");
    /* Set expunge bit so we don't get spurious reopened messages */
    idata->reopen |= IMAP_EXPUNGE_EXPECTED;
    if (imap_exec (idata, "EXPUNGE", 0) != 0)
    {
      imap_error (_("imap_sync_mailbox: EXPUNGE failed"), idata->cmd.buf);
      rc = -1;
      goto out;
    }
  }

  rc = 0;
 out:
  if (cmd.data)
    FREE (&cmd.data);
  if (appendctx)
  {
    mx_fastclose_mailbox (appendctx);
    FREE (&appendctx);
  }
  return rc;
}