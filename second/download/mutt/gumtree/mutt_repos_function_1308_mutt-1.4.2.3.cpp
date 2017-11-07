int imap_check_mailbox (CONTEXT *ctx, int *index_hint)
{
  /* overload keyboard timeout to avoid many mailbox checks in a row.
   * Most users don't like having to wait exactly when they press a key. */

  IMAP_DATA* idata;
  time_t now;
  int result = 0;

  idata = (IMAP_DATA*) ctx->data;

  now = time(NULL);
  if (now > ImapLastCheck + Timeout)
  {
    ImapLastCheck = now;

    if (imap_exec (idata, "NOOP", 0) != 0)
      return -1;
  }

  /* We call this even when we haven't run NOOP in case we have pending
   * changes to process, since we can reopen here. */
  imap_cmd_finish (idata);

  if (idata->check_status & IMAP_EXPUNGE_PENDING)
    result = M_REOPENED;
  else if (idata->check_status & IMAP_NEWMAIL_PENDING)
    result = M_NEW_MAIL;
  else if (idata->check_status & IMAP_FLAGS_PENDING)
    result = M_FLAGS;

  idata->check_status = 0;

  return result;
}