static void cmd_handle_fatal (IMAP_DATA* idata)
{
  idata->status = IMAP_FATAL;

  if ((idata->state >= IMAP_SELECTED) &&
      (idata->reopen & IMAP_REOPEN_ALLOW))
  {
    mx_fastclose_mailbox (idata->ctx);
    mutt_error (_("Mailbox closed"));
    mutt_sleep (1);
    idata->state = IMAP_DISCONNECTED;
  }

  if (idata->state < IMAP_SELECTED)
    imap_close_connection (idata);
}