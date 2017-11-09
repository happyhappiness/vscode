int imap_mailbox_create (const char* folder)
{
  IMAP_DATA* idata;
  IMAP_MBOX mx;
  char buf[LONG_STRING];
  short n;

  if (imap_parse_path (folder, &mx) < 0)
  {
    dprint (1, (debugfile, "imap_mailbox_create: Bad starting path %s\n",
      folder));
    return -1;
  }

  if (!(idata = imap_conn_find (&mx.account, MUTT_IMAP_CONN_NONEW)))
  {
    dprint (1, (debugfile, "imap_mailbox_create: Couldn't find open connection to %s", mx.account.host));
    goto fail;
  }
  
  strfcpy (buf, NONULL (mx.mbox), sizeof (buf));

  /* append a delimiter if necessary */
  n = mutt_strlen (buf);
  if (n && (n < sizeof (buf) - 1) && (buf[n-1] != idata->delim))
  {
    buf[n++] = idata->delim;
    buf[n] = '\0';
  }
  
  if (mutt_get_field (_("Create mailbox: "), buf, sizeof (buf), MUTT_FILE) < 0)
    goto fail;

  if (!mutt_strlen (buf))
  {
    mutt_error (_("Mailbox must have a name."));
    mutt_sleep(1);
    goto fail;
  }
  
  if (imap_create_mailbox (idata, buf) < 0)
    goto fail;

  mutt_message _("Mailbox created.");
  mutt_sleep (0);

  FREE (&mx.mbox);
  return 0;

 fail:
  FREE (&mx.mbox);
  return -1;
}