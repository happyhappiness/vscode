static int
dotlock_lock (const char *realpath)
{
  char lockfile[_POSIX_PATH_MAX + LONG_STRING];
  char nfslockfile[_POSIX_PATH_MAX + LONG_STRING];
  size_t prev_size = 0;
  int fd;
  int count = 0;
  int hard_count = 0;
  struct stat sb;
  time_t t;
  
  snprintf (nfslockfile, sizeof (nfslockfile), "%s.%s.%d",
	   realpath, Hostname, (int) getpid ());
  snprintf (lockfile, sizeof (lockfile), "%s.lock", realpath);

  
  BEGIN_PRIVILEGED ();

  unlink (nfslockfile);

  while ((fd = open (nfslockfile, O_WRONLY | O_EXCL | O_CREAT, 0)) < 0)
  {
    END_PRIVILEGED ();

  
    if (errno != EAGAIN)
    {
      /* perror ("cannot open NFS lock file"); */
      return DL_EX_ERROR;
    }

    
    BEGIN_PRIVILEGED ();
  }

  END_PRIVILEGED ();

  
  close (fd);
  
  while (hard_count++ < HARDMAXATTEMPTS)
  {

    BEGIN_PRIVILEGED ();
    link (nfslockfile, lockfile);
    END_PRIVILEGED ();

    if (stat (nfslockfile, &sb) != 0)
    {
      /* perror ("stat"); */
      return DL_EX_ERROR;
    }

    if (sb.st_nlink == 2)
      break;

    if (count == 0)
      prev_size = sb.st_size;

    if (prev_size == sb.st_size && ++count > Retry)
    {
      if (DotlockFlags & DL_FL_FORCE)
      {
	BEGIN_PRIVILEGED ();
	unlink (lockfile);
	END_PRIVILEGED ();

	count = 0;
	continue;
      }
      else
      {
	BEGIN_PRIVILEGED ();
	unlink (nfslockfile);
	END_PRIVILEGED ();
	return DL_EX_EXIST;
      }
    }
    
    prev_size = sb.st_size;
    
    /* don't trust sleep (3) as it may be interrupted
     * by users sending signals. 
     */
    
    t = time (NULL);
    do {
      sleep (1);
    } while (time (NULL) == t);
  }

  BEGIN_PRIVILEGED ();
  unlink (nfslockfile);
  END_PRIVILEGED ();

  return DL_EX_OK;
}