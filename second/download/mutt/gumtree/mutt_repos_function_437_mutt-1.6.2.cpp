static int buffy_maildir_hasnew (BUFFY* mailbox)
{
  if (buffy_maildir_dir_hasnew(mailbox, "new")) {
      return 1;
  }

  if (!option(OPTMAILDIRCHECKCUR)) {
      return 0;
  }

  if (buffy_maildir_dir_hasnew(mailbox, "cur")) {
      return 1;
  }

  return 0;
}