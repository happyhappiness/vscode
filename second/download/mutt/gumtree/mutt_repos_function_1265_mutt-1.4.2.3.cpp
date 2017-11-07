int imap_copy_messages (CONTEXT* ctx, HEADER* h, char* dest, int delete)
{
  IMAP_DATA* idata;
  BUFFER cmd;
  char uid[11];
  char mbox[LONG_STRING];
  char mmbox[LONG_STRING];
  int rc;
  int n;
  IMAP_MBOX mx;

  idata = (IMAP_DATA*) ctx->data;

  if (imap_parse_path (dest, &mx))
  {
    dprint (1, (debugfile, "imap_copy_messages: bad destination %s\n", dest));
    return -1;
  }

  /* check that the save-to folder is in the same account */
  if (!mutt_account_match (&(CTX_DATA->conn->account), &(mx.account)))
  {
    dprint (3, (debugfile, "imap_copy_messages: %s not same server as %s\n",
      dest, ctx->path));
    return 1;
  }

  if (h && h->attach_del)
  {
    dprint (3, (debugfile, "imap_copy_messages: Message contains attachments to be deleted\n"));
    return 1;
  }
  
  imap_fix_path (idata, mx.mbox, mbox, sizeof (mbox));

  memset (&cmd, 0, sizeof (cmd));
  mutt_buffer_addstr (&cmd, "UID COPY ");

  /* Null HEADER* means copy tagged messages */
  if (!h)
  {
    /* if any messages have attachments to delete, fall through to FETCH
     * and APPEND. TODO: Copy what we can with COPY, fall through for the
     * remainder. */
    for (n = 0; n < ctx->msgcount; n++)
    {
      if (ctx->hdrs[n]->tagged && ctx->hdrs[n]->attach_del)
      {
	dprint (3, (debugfile, "imap_copy_messages: Message contains attachments to be deleted\n"));
	return 1;
      }
    }

    rc = imap_make_msg_set (idata, &cmd, M_TAG, 0);
    if (!rc)
    {
      dprint (1, (debugfile, "imap_copy_messages: No messages tagged\n"));
      goto fail;
    }
    mutt_message (_("Copying %d messages to %s..."), rc, mbox);
  }
  else
  {
    mutt_message (_("Copying message %d to %s..."), h->index+1, mbox);
    snprintf (uid, sizeof (uid), "%u", HEADER_DATA (h)->uid);
    mutt_buffer_addstr (&cmd, uid);
  }

  /* let's get it on */
  mutt_buffer_addstr (&cmd, " ");
  imap_munge_mbox_name (mmbox, sizeof (mmbox), mbox);
  mutt_buffer_addstr (&cmd, mmbox);

  rc = imap_exec (idata, cmd.data, IMAP_CMD_FAIL_OK);
  if (rc == -2)
  {
    /* bail out if command failed for reasons other than nonexistent target */
    if (ascii_strncasecmp (imap_get_qualifier (idata->cmd.buf), "[TRYCREATE]", 11))
    {
      imap_error ("imap_copy_messages", idata->cmd.buf);
      goto fail;
    }
    dprint (2, (debugfile, "imap_copy_messages: server suggests TRYCREATE\n"));
    snprintf (mmbox, sizeof (mmbox), _("Create %s?"), mbox);
    if (option (OPTCONFIRMCREATE) && mutt_yesorno (mmbox, 1) < 1)
    {
      mutt_clear_error ();
      goto fail;
    }
    if (imap_create_mailbox (idata, mbox) < 0)
      goto fail;

    /* try again */
    rc = imap_exec (idata, cmd.data, 0);
  }
  if (rc != 0)
  {
    imap_error ("imap_copy_messages", idata->cmd.buf);
    goto fail;
  }

  /* cleanup */
  if (delete)
  {
    if (!h)
      for (n = 0; n < ctx->msgcount; n++)
      {
        if (ctx->hdrs[n]->tagged)
        {
          mutt_set_flag (ctx, ctx->hdrs[n], M_DELETE, 1);
          if (option (OPTDELETEUNTAG))
            mutt_set_flag (ctx, ctx->hdrs[n], M_TAG, 0);
        }
      }
    else
    {
      mutt_set_flag (ctx, h, M_DELETE, 1);
      if (option (OPTDELETEUNTAG))
        mutt_set_flag (ctx, h, M_TAG, 0);
    }
  }

  if (cmd.data)
    FREE (&cmd.data);
  FREE (&mx.mbox);
  return 0;

 fail:
  if (cmd.data)
    FREE (&cmd.data);
  FREE (&mx.mbox);
  return -1;
}