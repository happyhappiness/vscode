int imap_create_mailbox (IMAP_DATA* idata, char* mailbox)
{
  char buf[LONG_STRING], mbox[LONG_STRING];

  imap_munge_mbox_name (mbox, sizeof (mbox), mailbox);
  snprintf (buf, sizeof (buf), "CREATE %s", mbox);
      
  if (imap_exec (idata, buf, 0) != 0)
    return -1;

  return 0;
}