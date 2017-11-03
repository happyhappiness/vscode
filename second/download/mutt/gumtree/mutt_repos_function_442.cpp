static int buffy_maildir_check_dir (BUFFY* mailbox, const char *dir_name, int check_new,
                                    int check_stats)
{
  char path[_POSIX_PATH_MAX];
  char msgpath[_POSIX_PATH_MAX];
  DIR *dirp;
  struct dirent *de;
  char *p;
  int rc = 0;
  struct stat sb;

  snprintf (path, sizeof (path), "%s/%s", mailbox->path, dir_name);

  /* when $mail_check_recent is set, if the new/ directory hasn't been modified since
   * the user last exited the mailbox, then we know there is no recent mail.
   */
  if (check_new && option(OPTMAILCHECKRECENT))
  {
    if (stat(path, &sb) == 0 && sb.st_mtime < mailbox->last_visited)
    {
      rc = 0;
      check_new = 0;
    }
  }

  if (! (check_new || check_stats))
    return rc;

  if ((dirp = opendir (path)) == NULL)
  {
    mailbox->magic = 0;
    return 0;
  }

  while ((de = readdir (dirp)) != NULL)
  {
    if (*de->d_name == '.')
      continue;

    p = strstr (de->d_name, ":2,");
    if (p && strchr (p + 3, 'T'))
      continue;

    if (check_stats)
    {
      mailbox->msg_count++;
      if (p && strchr (p + 3, 'F'))
        mailbox->msg_flagged++;
    }
    if (!p || !strchr (p + 3, 'S'))
    {
      if (check_stats)
        mailbox->msg_unread++;
      if (check_new)
      {
        if (option(OPTMAILCHECKRECENT))
        {
          snprintf(msgpath, sizeof(msgpath), "%s/%s", path, de->d_name);
          /* ensure this message was received since leaving this mailbox */
          if (stat(msgpath, &sb) == 0 && (sb.st_ctime <= mailbox->last_visited))
            continue;
        }
        mailbox->new = 1;
        rc = 1;
        check_new = 0;
        if (!check_stats)
          break;
      }
    }
  }

  closedir (dirp);

  return rc;
}