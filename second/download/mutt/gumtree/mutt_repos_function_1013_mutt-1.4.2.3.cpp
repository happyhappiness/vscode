static int mh_mkstemp (CONTEXT *dest, FILE **fp, char **tgt)
{
  int fd;
  char path[_POSIX_PATH_MAX];

  FOREVER 
  {
    snprintf (path, _POSIX_PATH_MAX, "%s/.mutt-%s-%d-%d",
	      dest->path, NONULL (Hostname), (int) getpid (), Counter++);
    if ((fd = open (path, O_WRONLY | O_EXCL | O_CREAT, 0600)) == -1)
    {
      if (errno != EEXIST)
      {
	mutt_perror (path);
	return -1;
      }
    }
    else
    {
      *tgt = safe_strdup (path);
      break;
    }
  }

  if ((*fp = fdopen (fd, "w")) == NULL)
  {
    FREE (tgt);
    close (fd);
    unlink (path);
    return (-1);
  }
  
  return 0;
}