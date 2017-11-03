static void mx_unlink_empty (const char *path)
{
  int fd;
#ifndef USE_DOTLOCK
  struct stat sb;
#endif

  if ((fd = open (path, O_RDWR)) == -1)
    return;

  if (mx_lock_file (path, fd, 1, 0, 1) == -1)
  {
    close (fd);
    return;
  }

#ifdef USE_DOTLOCK
  invoke_dotlock (path, fd, DL_FL_UNLINK, 1);
#else
  if (fstat (fd, &sb) == 0 && sb.st_size == 0)
    unlink (path);
#endif

  mx_unlock_file (path, fd, 0);
  close (fd);
}