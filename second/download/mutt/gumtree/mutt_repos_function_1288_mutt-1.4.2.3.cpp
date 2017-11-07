int imap_access (const char* path, int flags)
{
  IMAP_DATA* idata;
  IMAP_MBOX mx;
  char buf[LONG_STRING];
  char mailbox[LONG_STRING];
  char mbox[LONG_STRING];

  if (imap_parse_path (path, &mx))
    return -1;

  if (!(idata = imap_conn_find (&mx.account,
    option (OPTIMAPPASSIVE) ? M_IMAP_CONN_NONEW : 0)))
  {
    FREE (&mx.mbox);
    return -1;
  }

  imap_fix_path (idata, mx.mbox, mailbox, sizeof (mailbox));
  FREE (&mx.mbox);
  imap_munge_mbox_name (mbox, sizeof (mbox), mailbox);

  /* TODO: ACL checks. Right now we assume if it exists we can mess with it. */
  if (mutt_bit_isset (idata->capabilities, IMAP4REV1))
    snprintf (buf, sizeof (buf), "STATUS %s (UIDVALIDITY)", mbox);
  else if (mutt_bit_isset (idata->capabilities, STATUS))
    snprintf (buf, sizeof (buf), "STATUS %s (UID-VALIDITY)", mbox);
  else
  {
    dprint (2, (debugfile, "imap_access: STATUS not supported?\n"));
    return -1;
  }

  if (imap_exec (idata, buf, IMAP_CMD_FAIL_OK) < 0)
  {
    dprint (1, (debugfile, "imap_access: Can't check STATUS of %s\n", mbox));
    return -1;
  }

  return 0;
}