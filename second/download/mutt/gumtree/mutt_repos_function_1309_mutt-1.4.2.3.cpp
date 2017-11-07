int imap_mailbox_check (char* path, int new)
{
  CONNECTION *conn;
  IMAP_DATA *idata;
  char buf[LONG_STRING];
  char mbox[LONG_STRING];
  char mbox_unquoted[LONG_STRING];
  char *s;
  int msgcount = 0;
  int connflags = 0;
  IMAP_MBOX mx;
  int rc;
  
  if (imap_parse_path (path, &mx))
    return -1;

  /* If imap_passive is set, don't open a connection to check for new mail */
  if (option (OPTIMAPPASSIVE))
    connflags = M_IMAP_CONN_NONEW;

  if (!(idata = imap_conn_find (&(mx.account), connflags)))
  {
    FREE (&mx.mbox);
    return -1;
  }
  conn = idata->conn;

  imap_fix_path (idata, mx.mbox, buf, sizeof (buf));
  FREE (&mx.mbox);

  imap_munge_mbox_name (mbox, sizeof(mbox), buf);
  strfcpy (mbox_unquoted, buf, sizeof (mbox_unquoted));

  /* The draft IMAP implementor's guide warns againts using the STATUS
   * command on a mailbox that you have selected 
   */

  if (mutt_strcmp (mbox_unquoted, idata->mailbox) == 0
      || (ascii_strcasecmp (mbox_unquoted, "INBOX") == 0
	  && mutt_strcasecmp (mbox_unquoted, idata->mailbox) == 0))
  {
    strfcpy (buf, "NOOP", sizeof (buf));
  }
  else if (mutt_bit_isset(idata->capabilities,IMAP4REV1) ||
	   mutt_bit_isset(idata->capabilities,STATUS))
  {				
    snprintf (buf, sizeof (buf), "STATUS %s (%s)", mbox,
      new ? "RECENT" : "MESSAGES");
  }
  else
    /* Server does not support STATUS, and this is not the current mailbox.
     * There is no lightweight way to check recent arrivals */
    return -1;

  imap_cmd_start (idata, buf);

  do 
  {
    if ((rc = imap_cmd_step (idata)) != IMAP_CMD_CONTINUE)
      break;

    s = imap_next_word (idata->cmd.buf);
    if (ascii_strncasecmp ("STATUS", s, 6) == 0)
    {
      s = imap_next_word (s);
      /* The mailbox name may or may not be quoted here. We could try to 
       * munge the server response and compare with quoted (or vise versa)
       * but it is probably more efficient to just strncmp against both. */
      if (mutt_strncmp (mbox_unquoted, s, mutt_strlen (mbox_unquoted)) == 0
	  || mutt_strncmp (mbox, s, mutt_strlen (mbox)) == 0)
      {
	s = imap_next_word (s);
	s = imap_next_word (s);
	if (isdigit (*s))
	{
	  if (*s != '0')
	  {
	    msgcount = atoi(s);
	    dprint (2, (debugfile, "%d new messages in %s\n", msgcount, path));
	  }
	}
      }
      else
	dprint (1, (debugfile, "imap_mailbox_check: STATUS response doesn't match requested mailbox.\n"));
    }
  }
  while (rc == IMAP_CMD_CONTINUE);

  return msgcount;
}