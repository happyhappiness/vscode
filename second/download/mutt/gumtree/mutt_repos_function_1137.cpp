int dotlock_invoke (const char *path, int fd, int flags, int retry)
{
  int currdir;
  int r;

  DotlockFlags = flags;
  
  if ((currdir = open (".", O_RDONLY)) == -1)
    return DL_EX_ERROR;

  if (!(DotlockFlags & DL_FL_RETRY) || retry)
    Retry = MAXLOCKATTEMPT;
  else
    Retry = 0;
  
  r = dotlock_dispatch (path, fd);
  
  fchdir (currdir);
  close (currdir);
  
  return r;
}