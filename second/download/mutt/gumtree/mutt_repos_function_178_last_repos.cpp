int mutt_rmtree (const char* path)
{
  DIR* dirp;
  struct dirent* de;
  char cur[_POSIX_PATH_MAX];
  struct stat statbuf;
  int rc = 0;

  if (!(dirp = opendir (path)))
  {
    dprint (1, (debugfile, "mutt_rmtree: error opening directory %s\n", path));
    return -1;
  }
  while ((de = readdir (dirp)))
  {
    if (!strcmp (".", de->d_name) || !strcmp ("..", de->d_name))
      continue;

    snprintf (cur, sizeof (cur), "%s/%s", path, de->d_name);
    /* XXX make nonrecursive version */

    if (stat(cur, &statbuf) == -1)
    {
      rc = 1;
      continue;
    }

    if (S_ISDIR (statbuf.st_mode))
      rc |= mutt_rmtree (cur);
    else
      rc |= unlink (cur);
  }
  closedir (dirp);

  rc |= rmdir (path);

  return rc;
}