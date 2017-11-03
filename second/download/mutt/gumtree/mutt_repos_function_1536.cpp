int maildir_check_empty (const char *path)
{
  DIR *dp;
  struct dirent *de;
  int r = 1; /* assume empty until we find a message */
  char realpath[_POSIX_PATH_MAX];
  int iter = 0;

  /* Strategy here is to look for any file not beginning with a period */

  do {
    /* we do "cur" on the first iteration since its more likely that we'll
     * find old messages without having to scan both subdirs
     */
    snprintf (realpath, sizeof (realpath), "%s/%s", path,
	      iter == 0 ? "cur" : "new");
    if ((dp = opendir (realpath)) == NULL)
      return -1;
    while ((de = readdir (dp)))
    {
      if (*de->d_name != '.')
      {
	r = 0;
	break;
      }
    }
    closedir (dp);
    iter++;
  } while (r && iter < 2);

  return r;
}