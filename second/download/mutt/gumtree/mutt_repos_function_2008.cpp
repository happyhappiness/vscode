int imap_mailbox_rename(const char* mailbox)
{
  IMAP_DATA* idata;
  IMAP_MBOX mx;
  char buf[LONG_STRING];
  char newname[SHORT_STRING];

  if (imap_parse_path (mailbox, &mx) < 0)
  {
    dprint (1, (debugfile, "imap_mailbox_rename: Bad source mailbox %s\n",
      mailbox));
    return -1;
  }

  if (!(idata = imap_conn_find (&mx.account, MUTT_IMAP_CONN_NONEW)))
  {
    dprint (1, (debugfile, "imap_mailbox_rename: Couldn't find open connection to %s", mx.account.host));
    goto fail;
  }

  if (!mx.mbox)
  {
    mutt_error _("Cannot rename root folder");
    goto fail;
  }

  snprintf(buf, sizeof (buf), _("Rename mailbox %s to: "), mx.mbox);
  strfcpy (newname, mx.mbox, sizeof (newname));
  
 if (mutt_get_field (buf, newname, sizeof (newname), MUTT_FILE) < 0)
    goto fail;

  if (!mutt_strlen (newname))
  {
    mutt_error (_("Mailbox must have a name."));
    mutt_sleep (1);
    goto fail;
  }

  imap_fix_path (idata, newname, buf, sizeof (buf));

  if (imap_rename_mailbox (idata, &mx, buf) < 0) {
    mutt_error (_("Rename failed: %s"), imap_get_qualifier (idata->buf));
    mutt_sleep (1);
    goto fail;
  }

  mutt_message (_("Mailbox renamed."));
  mutt_sleep (0);

  FREE (&mx.mbox);
  return 0;

 fail:
  FREE (&mx.mbox);
  return -1;
}