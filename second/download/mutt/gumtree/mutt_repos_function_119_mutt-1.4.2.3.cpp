int safe_open (const char *path, int flags)
{
  struct stat osb, nsb;
  int fd;

  if ((fd = open (path, flags, 0600)) < 0)
    return fd;

  /* make sure the file is not symlink */
  if (lstat (path, &osb) < 0 || fstat (fd, &nsb) < 0 ||
      compare_stat(&osb, &nsb) == -1)
  {
/*    dprint (1, (debugfile, "safe_open(): %s is a symlink!\n", path)); */
    close (fd);
    return (-1);
  }

  return (fd);
}