static int mh_mkstemp (CONTEXT * dest, FILE ** fp, char **tgt)
{
  int fd;
  char path[_POSIX_PATH_MAX];
  mode_t omask;

  omask = umask (mh_umask (dest));
  FOREVER
  {
    snprintf (path, _POSIX_PATH_MAX, "%s/.mutt-%s-%d-%d",
	      dest->path, NONULL (Hostname), (int) getpid (), Counter++);
    if ((fd = open (path, O_WRONLY | O_EXCL | O_CREAT, 0666)) == -1)
    {
      if (errno != EEXIST)
      {
	mutt_perror (path);
	umask (omask);
	return -1;
      }
    }
    else
    {
      *tgt = safe_strdup (path);
      break;
    }
  }
  umask (omask);

  if ((*fp = fdopen (fd, "w")) == NULL)
  {
    FREE (tgt);		/* __FREE_CHECKED__ */
    close (fd);
    unlink (path);
    return (-1);
  }

  return 0;
}