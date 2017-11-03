static FILE *_maildir_open_find_message (const char *folder, const char *unique,
				  const char *subfolder)
{
  char dir[_POSIX_PATH_MAX];
  char tunique[_POSIX_PATH_MAX];
  char fname[_POSIX_PATH_MAX];

  DIR *dp;
  struct dirent *de;

  FILE *fp = NULL;
  int oe = ENOENT;

  snprintf (dir, sizeof (dir), "%s/%s", folder, subfolder);

  if ((dp = opendir (dir)) == NULL)
  {
    errno = ENOENT;
    return NULL;
  }

  while ((de = readdir (dp)))
  {
    maildir_canon_filename (tunique, de->d_name, sizeof (tunique));

    if (!mutt_strcmp (tunique, unique))
    {
      snprintf (fname, sizeof (fname), "%s/%s/%s", folder, subfolder,
		de->d_name);
      fp = fopen (fname, "r");	/* __FOPEN_CHECKED__ */
      oe = errno;
      break;
    }
  }

  closedir (dp);

  errno = oe;
  return fp;
}