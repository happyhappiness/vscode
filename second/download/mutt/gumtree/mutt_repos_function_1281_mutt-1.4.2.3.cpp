static int cmd_handle_untagged (IMAP_DATA* idata)
{
  char* s;
  char* pn;
  int count;

  s = imap_next_word (idata->cmd.buf);

  if ((idata->state == IMAP_SELECTED) && isdigit (*s))
  {
    pn = s;
    s = imap_next_word (s);

    /* EXISTS and EXPUNGE are always related to the SELECTED mailbox for the
     * connection, so update that one.
     */
    if (ascii_strncasecmp ("EXISTS", s, 6) == 0)
    {
      dprint (2, (debugfile, "Handling EXISTS\n"));

      /* new mail arrived */
      count = atoi (pn);

      if ( !(idata->reopen & IMAP_EXPUNGE_PENDING) &&
	   count < idata->ctx->msgcount)
      {
	/* something is wrong because the server reported fewer messages
	 * than we previously saw
	 */
	mutt_error _("Fatal error.  Message count is out of sync!");
	idata->status = IMAP_FATAL;
	return -1;
      }
      /* at least the InterChange server sends EXISTS messages freely,
       * even when there is no new mail */
      else if (count == idata->ctx->msgcount)
	dprint (3, (debugfile,
          "cmd_handle_untagged: superfluous EXISTS message.\n"));
      else
      {
	if (!(idata->reopen & IMAP_EXPUNGE_PENDING))
        {
          dprint (2, (debugfile,
            "cmd_handle_untagged: New mail in %s - %d messages total.\n",
            idata->mailbox, count));
	  idata->reopen |= IMAP_NEWMAIL_PENDING;
        }
	idata->newMailCount = count;
      }
    }
    /* pn vs. s: need initial seqno */
    else if (ascii_strncasecmp ("EXPUNGE", s, 7) == 0)
      cmd_parse_expunge (idata, pn);
    else if (ascii_strncasecmp ("FETCH", s, 5) == 0)
      cmd_parse_fetch (idata, pn);
  }
  else if (ascii_strncasecmp ("CAPABILITY", s, 10) == 0)
    cmd_parse_capabilities (idata, s);
  else if (ascii_strncasecmp ("MYRIGHTS", s, 8) == 0)
    cmd_parse_myrights (idata, s);
  else if (ascii_strncasecmp ("BYE", s, 3) == 0)
  {
    dprint (2, (debugfile, "Handling BYE\n"));

    /* check if we're logging out */
    if (idata->status == IMAP_BYE)
      return 0;

    /* server shut down our connection */
    s += 3;
    SKIPWS (s);
    mutt_error ("%s", s);
    idata->status = IMAP_BYE;
    if (idata->state == IMAP_SELECTED)
      mx_fastclose_mailbox (idata->ctx);
    mutt_socket_close (idata->conn);
    idata->state = IMAP_DISCONNECTED;

    return -1;
  }
  else if (option (OPTIMAPSERVERNOISE) && (ascii_strncasecmp ("NO", s, 2) == 0))
  {
    dprint (2, (debugfile, "Handling untagged NO\n"));

    /* Display the warning message from the server */
    mutt_error ("%s", s+3);
    mutt_sleep (2);
  }

  return 0;
}