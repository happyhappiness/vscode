int imap_open_mailbox_append (CONTEXT *ctx)
{
  CONNECTION *conn;
  IMAP_DATA *idata;
  char buf[LONG_STRING], mbox[LONG_STRING];
  char mailbox[LONG_STRING];
  int r;
  IMAP_MBOX mx;

  if (imap_parse_path (ctx->path, &mx))
    return -1;

  /* in APPEND mode, we appear to hijack an existing IMAP connection -
   * ctx is brand new and mostly empty */

  if (!(idata = imap_conn_find (&(mx.account), 0)))
    goto fail;
  conn = idata->conn;

  ctx->magic = M_IMAP;
  ctx->data = (void *) idata;

  /* check mailbox existance */

  imap_fix_path (idata, mx.mbox, mailbox, sizeof (mailbox));

  imap_munge_mbox_name (mbox, sizeof (mbox), mailbox);
				
  if (mutt_bit_isset(idata->capabilities,IMAP4REV1))
    snprintf (buf, sizeof (buf), "STATUS %s (UIDVALIDITY)", mbox);
  else if (mutt_bit_isset(idata->capabilities,STATUS))
    /* We have no idea what the other guy wants. UW imapd 8.3 wants this
     * (but it does not work if another mailbox is selected) */
    snprintf (buf, sizeof (buf), "STATUS %s (UID-VALIDITY)", mbox);
  else
  {
    /* STATUS not supported */
    mutt_message _("Unable to append to IMAP mailboxes at this server");

    goto fail;
  }

  r = imap_exec (idata, buf, IMAP_CMD_FAIL_OK);
  if (r == -2)
  {
    /* command failed cause folder doesn't exist */
    snprintf (buf, sizeof (buf), _("Create %s?"), mailbox);
    if (option (OPTCONFIRMCREATE) && mutt_yesorno (buf, 1) < 1)
      goto fail;

    if (imap_create_mailbox (idata, mailbox) < 0)
      goto fail;
  }
  else if (r == -1)
    /* Hmm, some other failure */
    goto fail;

  FREE (&mx.mbox);
  return 0;

 fail:
  FREE (&mx.mbox);
  return -1;
}