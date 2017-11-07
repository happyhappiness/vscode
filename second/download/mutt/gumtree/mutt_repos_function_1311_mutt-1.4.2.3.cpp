int imap_subscribe (char *path, int subscribe)
{
  CONNECTION *conn;
  IMAP_DATA *idata;
  char buf[LONG_STRING];
  char mbox[LONG_STRING];
  IMAP_MBOX mx;

  if (!mx_is_imap (path) || imap_parse_path (path, &mx))
  {
    mutt_error (_("Bad mailbox name"));
    return -1;
  }
  

  if (!(idata = imap_conn_find (&(mx.account), 0)))
    goto fail;
  
  conn = idata->conn;

  imap_fix_path (idata, mx.mbox, buf, sizeof (buf));
  if (subscribe)
    mutt_message (_("Subscribing to %s..."), buf);
  else
    mutt_message (_("Unsubscribing to %s..."), buf);
  imap_munge_mbox_name (mbox, sizeof(mbox), buf);

  snprintf (buf, sizeof (buf), "%s %s", subscribe ? "SUBSCRIBE" :
    "UNSUBSCRIBE", mbox);

  if (imap_exec (idata, buf, 0) < 0)
    goto fail;

  FREE (&mx.mbox);
  return 0;

 fail:
  FREE (&mx.mbox);
  return -1;
}