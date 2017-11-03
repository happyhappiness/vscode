FILE *safe_fopen (const char *path, const char *mode)
{
  if (mode[0] == 'w')
  {
    int fd;
    int flags = O_CREAT | O_EXCL;

#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif

    if (mode[1] == '+')
      flags |= O_RDWR;
    else
      flags |= O_WRONLY;

    if ((fd = safe_open (path, flags)) < 0)
      return (NULL);

    return (fdopen (fd, mode));
  }
  else
    return (fopen (path, mode));
}