int mh_buffy (BUFFY *mailbox, int check_stats)
{
  int i;
  struct mh_sequences mhs;
  int check_new = 1;
  int rc = 0;
  DIR *dirp;
  struct dirent *de;

  /* when $mail_check_recent is set and the .mh_sequences file hasn't changed
   * since the last mailbox visit, there is no "new mail" */
  if (option(OPTMAILCHECKRECENT) && mh_sequences_changed(mailbox) <= 0)
  {
    rc = 0;
    check_new = 0;
  }

  if (! (check_new || check_stats))
    return rc;

  memset (&mhs, 0, sizeof (mhs));
  if (mh_read_sequences (&mhs, mailbox->path) < 0)
    return 0;

  if (check_stats)
  {
    mailbox->msg_count   = 0;
    mailbox->msg_unread  = 0;
    mailbox->msg_flagged = 0;
  }

  for (i = mhs.max; i > 0; i--)
  {
    if (check_stats &&
        (mhs_check (&mhs, i) & MH_SEQ_FLAGGED))
      mailbox->msg_flagged++;
    if (mhs_check (&mhs, i) & MH_SEQ_UNSEEN)
    {
      if (check_stats)
        mailbox->msg_unread++;
      if (check_new)
      {
        /* if the first unseen message we encounter was in the mailbox during the
           last visit, don't notify about it */
        if (!option(OPTMAILCHECKRECENT) || mh_already_notified(mailbox, i) == 0)
        {
          mailbox->new = 1;
          rc = 1;
        }
        /* Because we are traversing from high to low, we can stop
         * checking for new mail after the first unseen message.
         * Whether it resulted in "new mail" or not. */
        check_new = 0;
        if (!check_stats)
          break;
      }
    }
  }
  mhs_free_sequences (&mhs);

  if (check_stats)
  {
    if ((dirp = opendir (mailbox->path)) != NULL)
    {
      while ((de = readdir (dirp)) != NULL)
      {
        if (*de->d_name == '.')
          continue;
        if (mh_valid_message (de->d_name))
          mailbox->msg_count++;
      }
      closedir (dirp);
    }
  }

  return rc;
}