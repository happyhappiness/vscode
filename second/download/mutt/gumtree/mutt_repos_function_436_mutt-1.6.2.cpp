static int buffy_maildir_dir_hasnew(BUFFY* mailbox, const char *dir_name)
{
  char path[_POSIX_PATH_MAX];
  DIR *dirp;
  struct dirent *de;
  char *p;
  int rc = 0;
  struct stat sb;

  snprintf (path, sizeof (path), "%s/%s", mailbox->path, dir_name);

  /* when $mail_check_recent is set, if the new/ directory hasn't been modified since
   * the user last exited the mailbox, then we know there is no recent mail.
   */
  if (option(OPTMAILCHECKRECENT))
  {
    if (stat(path, &sb) == 0 && sb.st_mtime < mailbox->last_visited)
      return 0;
  }

  if ((dirp = opendir (path)) == NULL)
  {
    mailbox->magic = 0;
    return 0;
  }

  while ((de = readdir (dirp)) != NULL)
  {
    if (*de->d_name == '.')
      continue;

    if (!(p = strstr (de->d_name, ":2,")) || !(strchr (p + 3, 'T') || strchr(p + 3, 'S')))
    {
      if (option(OPTMAILCHECKRECENT))
      {
	char msgpath[_POSIX_PATH_MAX];

	snprintf(msgpath, sizeof(msgpath), "%s/%s", path, de->d_name);
	/* ensure this message was received since leaving this mailbox */
	if (stat(msgpath, &sb) == 0 && (sb.st_ctime <= mailbox->last_visited))
	  continue;
      }
      /* one new and undeleted message is enough */
      mailbox->new = 1;
      rc = 1;
      break;
    }
  }

  closedir (dirp);

  return rc;
}