static int buffy_maildir_check (BUFFY* mailbox, int check_stats)
{
  int rc, check_new = 1;

  if (check_stats)
  {
    mailbox->msg_count   = 0;
    mailbox->msg_unread  = 0;
    mailbox->msg_flagged = 0;
  }

  rc = buffy_maildir_check_dir (mailbox, "new", check_new, check_stats);

  check_new = !rc && option (OPTMAILDIRCHECKCUR);
  if (check_new || check_stats)
    if (buffy_maildir_check_dir (mailbox, "cur", check_new, check_stats))
      rc = 1;

  return rc;
}