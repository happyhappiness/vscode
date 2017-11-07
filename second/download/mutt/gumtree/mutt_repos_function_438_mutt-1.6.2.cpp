static int buffy_mbox_hasnew (BUFFY* mailbox, struct stat *sb)
{
  int rc = 0;
  int statcheck;

  if (option (OPTCHECKMBOXSIZE))
    statcheck = sb->st_size > mailbox->size;
  else
    statcheck = sb->st_mtime > sb->st_atime
      || (mailbox->newly_created && sb->st_ctime == sb->st_mtime && sb->st_ctime == sb->st_atime);
  if (statcheck)
  {
    if (!option(OPTMAILCHECKRECENT) || sb->st_mtime > mailbox->last_visited)
    {
      rc = 1;
      mailbox->new = 1;
    }
  }
  else if (option(OPTCHECKMBOXSIZE))
  {
    /* some other program has deleted mail from the folder */
    mailbox->size = (off_t) sb->st_size;
  }
  if (mailbox->newly_created &&
      (sb->st_ctime != sb->st_mtime || sb->st_ctime != sb->st_atime))
    mailbox->newly_created = 0;

  return rc;
}