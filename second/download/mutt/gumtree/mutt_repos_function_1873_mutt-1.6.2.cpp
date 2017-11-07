int imap_rename_mailbox (IMAP_DATA* idata, IMAP_MBOX* mx, const char* newname)
{
  char oldmbox[LONG_STRING];
  char newmbox[LONG_STRING];
  char buf[LONG_STRING];

  imap_munge_mbox_name (idata, oldmbox, sizeof (oldmbox), mx->mbox);
  imap_munge_mbox_name (idata, newmbox, sizeof (newmbox), newname);

  snprintf (buf, sizeof (buf), "RENAME %s %s", oldmbox, newmbox);

  if (imap_exec (idata, buf, 0) != 0)
    return -1;

  return 0;
}