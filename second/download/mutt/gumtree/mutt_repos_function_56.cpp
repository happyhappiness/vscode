static int
dotlock_prepare (char *bn, size_t l, const char *f, int _fd)
{
  struct stat fsb, lsb;
  char realpath[_POSIX_PATH_MAX];
  char *basename, *dirname;
  char *p;
  int fd;
  int r;
  
  if (dotlock_deference_symlink (realpath, sizeof (realpath), f) == -1)
    return -1;
  
  if ((p = strrchr (realpath, '/')))
  {
    *p = '\0';
    basename = p + 1;
    dirname = realpath;
  }
  else
  {
    basename = realpath;
    dirname = ".";
  }

  if (strlen (basename) + 1 > l)
    return -1;
  
  strfcpy (bn, basename, l);
  
  if (chdir (dirname) == -1)
    return -1;

  if (_fd != -1)
    fd = _fd;
  else if ((fd = open (basename, O_RDONLY)) == -1)
    return -1;
  
  r = fstat (fd, &fsb);
  
  if (_fd == -1)
    close (fd);
  
  if (r == -1)
    return -1;
  
  if (lstat (basename, &lsb) == -1)
    return -1;

  if (dotlock_check_stats (&fsb, &lsb) == -1)
    return -1;

  return 0;
}