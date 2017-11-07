int safe_open (const char *path, int flags)
{
  struct stat osb, nsb;
  int fd;

  if (flags & O_EXCL) 
  {
    char safe_file[_POSIX_PATH_MAX];
    char safe_dir[_POSIX_PATH_MAX];

    if (mutt_mkwrapdir (path, safe_file, sizeof (safe_file),
			safe_dir, sizeof (safe_dir)) == -1)
      return -1;
    
    if ((fd = open (safe_file, flags, 0600)) < 0)
    {
      rmdir (safe_dir);
      return fd;
    }

    /* NFS and I believe cygwin do not handle movement of open files well */
    close (fd);
    if (mutt_put_file_in_place (path, safe_file, safe_dir) == -1)
      return -1;
  }

  if ((fd = open (path, flags & ~O_EXCL, 0600)) < 0)
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