static int imap_check_acl (IMAP_DATA *idata)
{
  char buf[LONG_STRING];
  char mbox[LONG_STRING];

  imap_munge_mbox_name (mbox, sizeof(mbox), idata->mailbox);
  snprintf (buf, sizeof (buf), "MYRIGHTS %s", mbox);
  if (imap_exec (idata, buf, 0) != 0)
  {
    imap_error ("imap_check_acl", buf);
    return -1;
  }
  return 0;
}