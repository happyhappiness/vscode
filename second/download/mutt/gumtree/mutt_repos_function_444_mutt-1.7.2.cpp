static int buffy_mbox_check (BUFFY* mailbox, struct stat *sb, int check_stats)
{
  int rc = 0;
  int new_or_changed;
  CONTEXT ctx;

  if (option (OPTCHECKMBOXSIZE))
    new_or_changed = sb->st_size > mailbox->size;
  else
    new_or_changed = sb->st_mtime > sb->st_atime
      || (mailbox->newly_created && sb->st_ctime == sb->st_mtime && sb->st_ctime == sb->st_atime);

  if (new_or_changed)
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

  if (check_stats &&
      (mailbox->stats_last_checked < sb->st_mtime))
  {
    if (mx_open_mailbox (mailbox->path,
                         MUTT_READONLY | MUTT_QUIET | MUTT_NOSORT | MUTT_PEEK,
                         &ctx) != NULL)
    {
      mailbox->msg_count       = ctx.msgcount;
      mailbox->msg_unread      = ctx.unread;
      mailbox->msg_flagged     = ctx.flagged;
      mailbox->stats_last_checked = ctx.mtime;
      mx_close_mailbox (&ctx, 0);
    }
  }

  return rc;
}